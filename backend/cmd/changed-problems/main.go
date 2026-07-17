// Command changed-problems selects current testcase problems affected by a Git diff.
package main

import (
	"bytes"
	"encoding/json"
	"errors"
	"flag"
	"fmt"
	"io"
	"os"
	"os/exec"
	"path"
	"path/filepath"
	"sort"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/internal/authorindex"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
)

type commandResult struct {
	AffectedProblemDirs  []string `json:"affectedProblemDirs"`
	UnownedTestcasePaths []string `json:"unownedTestcasePaths"`
}

func main() {
	if err := run(os.Args[1:], os.Stdout); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}

func run(args []string, output io.Writer) error {
	flags := flag.NewFlagSet("changed-problems", flag.ContinueOnError)
	flags.SetOutput(io.Discard)
	repoRoot := flags.String("repo-root", "", "path to the repository root")
	base := flags.String("base", "", "Git base revision")
	if err := flags.Parse(args); err != nil {
		return err
	}
	if strings.TrimSpace(*repoRoot) == "" || strings.TrimSpace(*base) == "" || flags.NArg() != 0 {
		return errors.New("usage: changed-problems --repo-root <path> --base <ref>")
	}

	logicalToPhysical, err := authorindex.LogicalToPhysical(*repoRoot)
	if err != nil {
		return fmt.Errorf("index testcase paths: %w", err)
	}
	changed, err := gitChangedPaths(*repoRoot, *base)
	if err != nil {
		return err
	}
	result, err := selectProblems(changed, logicalToPhysical, func(filePath string) (string, error) {
		return problemDirForPath(*repoRoot, filePath)
	})
	if err != nil {
		return err
	}
	if err := json.NewEncoder(output).Encode(result); err != nil {
		return fmt.Errorf("encode result: %w", err)
	}
	return nil
}

func gitChangedPaths(repoRoot, base string) ([]string, error) {
	output, err := exec.Command(
		"git", "-C", repoRoot, "diff", "--name-only", "-z", "--no-renames", base, "HEAD", "--",
	).CombinedOutput()
	if err != nil {
		return nil, fmt.Errorf("list changed paths: %w: %s", err, strings.TrimSpace(string(output)))
	}
	parts := bytes.Split(output, []byte{0})
	paths := make([]string, 0, len(parts))
	for _, part := range parts {
		if len(part) > 0 {
			paths = append(paths, string(part))
		}
	}
	return paths, nil
}

func selectProblems(
	changedPaths []string,
	logicalToPhysical map[string]string,
	findProblemDir func(string) (string, error),
) (commandResult, error) {
	affected := map[string]bool{}
	unowned := map[string]bool{}

	for _, changedPath := range changedPaths {
		if !strings.HasPrefix(changedPath, "testcase/") {
			continue
		}
		problemDir, err := findProblemDir(changedPath)
		if err != nil {
			return commandResult{}, err
		}
		if problemDir == "" {
			unowned[changedPath] = true
		} else {
			affected[problemDir] = true
		}

		logicalPath := strings.TrimPrefix(changedPath, "testcase/")
		physicalPath, ok := logicalToPhysical[logicalPath]
		if !ok || physicalPath != logicalPath {
			continue
		}
		for consumerPath, consumerTarget := range logicalToPhysical {
			if consumerTarget != physicalPath {
				continue
			}
			problemDir, err := findProblemDir("testcase/" + consumerPath)
			if err != nil {
				return commandResult{}, err
			}
			if problemDir != "" {
				affected[problemDir] = true
			}
		}
	}

	return commandResult{
		AffectedProblemDirs:  sortedKeys(affected),
		UnownedTestcasePaths: sortedKeys(unowned),
	}, nil
}

func problemDirForPath(repoRoot, repoPath string) (string, error) {
	for _, candidate := range []string{repoPath, path.Dir(repoPath)} {
		fullPath := filepath.Join(repoRoot, filepath.FromSlash(candidate))
		info, err := os.Stat(fullPath)
		if errors.Is(err, os.ErrNotExist) {
			continue
		}
		if err != nil {
			return "", fmt.Errorf("inspect problem directory %s: %w", candidate, err)
		}
		if !info.IsDir() {
			continue
		}
		isProblem, err := loader.IsProblemDir(fullPath)
		if err != nil {
			return "", fmt.Errorf("inspect problem markers in %s: %w", candidate, err)
		}
		if isProblem {
			return candidate, nil
		}
	}
	return "", nil
}

func sortedKeys(values map[string]bool) []string {
	result := make([]string, 0, len(values))
	for value := range values {
		result = append(result, value)
	}
	sort.Strings(result)
	return result
}
