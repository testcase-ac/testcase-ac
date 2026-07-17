package authorindex

import (
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"sort"
	"strings"
	"syscall"

	"gopkg.in/yaml.v3"
)

// dependencies isolates Build's I/O adapters so buildWithDependencies can be
// unit-tested with in-memory maps instead of Git, symlinks, and metadata files.
// Each function receives the repository root as its first argument. All
// returned paths are slash-separated and relative to testcase/.
type dependencies struct {
	// loadLogicalToPhysical returns every current logical file mapped to its
	// final physical donor. The result defines the complete final index key set;
	// a missing testcase directory returns an empty map.
	loadLogicalToPhysical func(string) (map[string]string, error)

	// loadGitAuthors returns physical paths mapped to their latest committed
	// author. Paths with no Git history are absent, latest deletions map to "",
	// and a non-Git repository returns an empty map.
	loadGitAuthors func(string) (map[string]string, error)

	// loadOverrides returns physical paths with explicit metadata author
	// overrides. Its second argument is the deduplicated list of current physical
	// donor paths; paths without an override are absent, and unreadable or
	// malformed metadata returns an error.
	loadOverrides func(string, []string) (map[string]string, error)
}

// Build produces final authors for the current logical testcase tree.
func Build(repoRoot string) (map[string]string, error) {
	return buildWithDependencies(repoRoot, dependencies{
		loadLogicalToPhysical: LogicalToPhysical,
		loadGitAuthors:        buildGitAuthors,
		loadOverrides:         buildPhysicalOverrides,
	})
}

func buildWithDependencies(repoRoot string, deps dependencies) (map[string]string, error) {
	logicalToPhysical, err := deps.loadLogicalToPhysical(repoRoot)
	if err != nil {
		return nil, fmt.Errorf("build logical testcase paths: %w", err)
	}
	gitAuthors, err := deps.loadGitAuthors(repoRoot)
	if err != nil {
		return nil, fmt.Errorf("build Git authors: %w", err)
	}
	overrides, err := deps.loadOverrides(repoRoot, uniquePhysicalPaths(logicalToPhysical))
	if err != nil {
		return nil, fmt.Errorf("build metadata author overrides: %w", err)
	}
	return composeAuthors(logicalToPhysical, gitAuthors, overrides), nil
}

func uniquePhysicalPaths(logicalToPhysical map[string]string) []string {
	seen := make(map[string]struct{}, len(logicalToPhysical))
	for _, physicalPath := range logicalToPhysical {
		seen[physicalPath] = struct{}{}
	}
	paths := make([]string, 0, len(seen))
	for physicalPath := range seen {
		paths = append(paths, physicalPath)
	}
	sort.Strings(paths)
	return paths
}

// composeAuthors applies physical metadata overrides before physical Git authors.
func composeAuthors(logicalToPhysical, gitAuthors, overrides map[string]string) map[string]string {
	result := make(map[string]string, len(logicalToPhysical))
	for logicalPath, physicalPath := range logicalToPhysical {
		if author, ok := overrides[physicalPath]; ok {
			result[logicalPath] = author
			continue
		}
		result[logicalPath] = gitAuthors[physicalPath]
	}
	return result
}

// buildGitAuthors derives latest authors from a single Git history scan.
func buildGitAuthors(repoRoot string) (map[string]string, error) {
	// Non-Git fixtures have no automatic Git attribution. Filesystem metadata
	// overrides are still collected by the other adapters.
	if _, err := os.Stat(filepath.Join(repoRoot, ".git")); err != nil {
		if errors.Is(err, os.ErrNotExist) {
			return map[string]string{}, nil
		}
		return nil, fmt.Errorf("inspect Git repository: %w", err)
	}

	// Git emits commits newest first. Each author marker applies to the path
	// lines that follow it until the next commit marker.
	cmd := exec.Command(
		"git", "-C", repoRoot, "log",
		"--format=__AUTHOR__%an%x00%ae",
		"--name-status",
		"--no-renames",
		"--", "testcase",
	)
	output, err := cmd.Output()
	if err != nil {
		return nil, fmt.Errorf("build author index: %w", err)
	}

	// The first occurrence of a path is its latest committed state. A deletion
	// records an empty author so older history cannot attribute an untracked
	// replacement that happens to reuse the same path.
	authorByRelPath := make(map[string]string)
	currentAuthor := ""
	for rawLine := range bytes.SplitSeq(output, []byte{'\n'}) {
		line := strings.TrimSpace(string(rawLine))
		if line == "" {
			continue
		}
		if after, ok := strings.CutPrefix(line, "__AUTHOR__"); ok {
			payload := after
			authorName, authorEmail, _ := strings.Cut(payload, "\x00")
			currentAuthor = contributorLabel(authorName, authorEmail)
			continue
		}
		status, path, ok := strings.Cut(line, "\t")
		if !ok || currentAuthor == "" || !strings.HasPrefix(path, "testcase/") {
			continue
		}
		relPath := strings.TrimPrefix(filepath.ToSlash(path), "testcase/")
		if _, exists := authorByRelPath[relPath]; exists {
			continue
		}
		if status == "D" {
			authorByRelPath[relPath] = ""
			continue
		}
		authorByRelPath[relPath] = currentAuthor
	}

	return authorByRelPath, nil
}

// LogicalToPhysical maps every current logical testcase file to its resolved target.
func LogicalToPhysical(repoRoot string) (map[string]string, error) {
	testcaseRoot, err := filepath.EvalSymlinks(filepath.Join(repoRoot, "testcase"))
	if err != nil {
		if errors.Is(err, os.ErrNotExist) {
			return map[string]string{}, nil
		}
		return nil, fmt.Errorf("resolve testcase root: %w", err)
	}
	logicalFiles, err := listLogicalFiles(testcaseRoot)
	if err != nil {
		return nil, err
	}

	logicalToPhysical := make(map[string]string, len(logicalFiles))
	for _, logicalRel := range logicalFiles {
		logicalPath := filepath.Join(testcaseRoot, filepath.FromSlash(logicalRel))
		physicalRel, err := resolveWithin(testcaseRoot, logicalPath)
		if err != nil {
			return nil, fmt.Errorf("resolve testcase path %s: %w", logicalPath, err)
		}
		logicalToPhysical[logicalRel] = filepath.ToSlash(physicalRel)
	}
	return logicalToPhysical, nil
}

// buildPhysicalOverrides reads each donor directory's metadata at most once.
func buildPhysicalOverrides(repoRoot string, physicalPaths []string) (map[string]string, error) {
	overrides := make(map[string]string)
	if len(physicalPaths) == 0 {
		return overrides, nil
	}
	testcaseRoot, err := filepath.EvalSymlinks(filepath.Join(repoRoot, "testcase"))
	if err != nil {
		return nil, fmt.Errorf("resolve testcase root: %w", err)
	}

	authorsByDir := make(map[string]map[string]string)
	for _, physicalRel := range physicalPaths {
		physicalPath := filepath.FromSlash(physicalRel)
		dirRel := filepath.Dir(physicalPath)
		authors, loaded := authorsByDir[dirRel]
		if !loaded {
			metadataPath := filepath.Join(testcaseRoot, dirRel, "metadata.yaml")
			data, err := os.ReadFile(metadataPath)
			if err != nil && !errors.Is(err, os.ErrNotExist) {
				return nil, fmt.Errorf("read author metadata %s: %w", metadataPath, err)
			}
			if err == nil {
				var metadata struct {
					Authors map[string]string `yaml:"authors"`
				}
				if err := yaml.Unmarshal(data, &metadata); err != nil {
					return nil, fmt.Errorf("parse author metadata %s: %w", metadataPath, err)
				}
				authors = metadata.Authors
			}
			authorsByDir[dirRel] = authors
		}
		if author, ok := authors[filepath.Base(physicalPath)]; ok {
			overrides[physicalRel] = author
		}
	}
	return overrides, nil
}

// listLogicalFiles starts a logical-tree walk with fresh directory-cycle state.
func listLogicalFiles(testcaseRoot string) ([]string, error) {
	return walkLogicalDir(testcaseRoot, "", make(map[string]bool))
}

func walkLogicalDir(root, logicalDirRel string, activeDirs map[string]bool) ([]string, error) {
	logicalDir := filepath.Join(root, logicalDirRel)
	physicalDirRel, err := resolveWithin(root, logicalDir)
	if err != nil {
		return nil, fmt.Errorf("resolve testcase directory %s: %w", logicalDir, err)
	}
	if activeDirs[physicalDirRel] {
		return nil, fmt.Errorf("cyclic testcase directory symlink at %s", logicalDir)
	}
	activeDirs[physicalDirRel] = true
	defer delete(activeDirs, physicalDirRel)

	entries, err := os.ReadDir(logicalDir)
	if err != nil {
		return nil, fmt.Errorf("read testcase directory %s: %w", logicalDir, err)
	}
	var files []string
	for _, entry := range entries {
		logicalRel := filepath.Join(logicalDirRel, entry.Name())
		logicalPath := filepath.Join(root, logicalRel)
		if entry.Type()&os.ModeSymlink != 0 {
			target, err := os.Readlink(logicalPath)
			if err != nil {
				return nil, err
			}
			if filepath.IsAbs(target) {
				return nil, fmt.Errorf("absolute testcase symlink at %s", logicalPath)
			}
		}
		info, err := os.Stat(logicalPath)
		if err != nil {
			if errors.Is(err, syscall.ELOOP) {
				return nil, fmt.Errorf("cyclic testcase symlink at %s", logicalPath)
			}
			return nil, fmt.Errorf("resolve testcase path %s: %w", logicalPath, err)
		}
		if info.IsDir() {
			descendants, err := walkLogicalDir(root, logicalRel, activeDirs)
			if err != nil {
				return nil, err
			}
			files = append(files, descendants...)
			continue
		}
		if info.Mode().IsRegular() {
			files = append(files, filepath.ToSlash(logicalRel))
		}
	}
	return files, nil
}

func resolveWithin(root, path string) (string, error) {
	physicalPath, err := filepath.EvalSymlinks(path)
	if err != nil {
		return "", err
	}
	rel, err := filepath.Rel(root, physicalPath)
	if err != nil {
		return "", err
	}
	if !filepath.IsLocal(rel) {
		return "", fmt.Errorf("target leaves testcase")
	}
	return rel, nil
}

// ReadFile decodes an author index manifest from path.
func ReadFile(path string) (map[string]string, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return nil, fmt.Errorf("read author index: %w", err)
	}
	var index map[string]string
	if err := json.Unmarshal(data, &index); err != nil {
		return nil, fmt.Errorf("parse author index: %w", err)
	}
	return index, nil
}

// WriteFile encodes an author index manifest at path.
func WriteFile(path string, index map[string]string) error {
	data, err := json.Marshal(index)
	if err != nil {
		return fmt.Errorf("encode author index: %w", err)
	}
	if err := os.WriteFile(path, data, 0o644); err != nil {
		return fmt.Errorf("write author index: %w", err)
	}
	return nil
}

func contributorLabel(authorName, authorEmail string) string {
	email := strings.TrimSpace(authorEmail)
	if email != "" {
		local, domain, found := strings.Cut(email, "@")
		if found && domain == "users.noreply.github.com" {
			if _, username, plus := strings.Cut(local, "+"); plus {
				if strings.TrimSpace(username) != "" {
					return strings.TrimSpace(username)
				}
			}
			return strings.TrimSpace(local)
		}
		return strings.TrimSpace(local)
	}
	return strings.TrimSpace(authorName)
}
