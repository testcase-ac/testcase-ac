package authorindex

import (
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

// Build returns the latest Git author for every exact path seen under testcase/.
func Build(repoRoot string) (map[string]string, error) {
	// Non-Git fixtures have no automatic attribution, but still produce a valid
	// empty manifest for the same backend startup path.
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
		"--name-only",
		"--", "testcase",
	)
	output, err := cmd.Output()
	if err != nil {
		return nil, fmt.Errorf("build author index: %w", err)
	}

	// The first occurrence of a path is its latest author. Older occurrences
	// are intentionally ignored once the path has been recorded.
	authorByRelPath := make(map[string]string)
	currentAuthor := ""
	for _, rawLine := range bytes.Split(output, []byte{'\n'}) {
		line := strings.TrimSpace(string(rawLine))
		if line == "" {
			continue
		}
		if strings.HasPrefix(line, "__AUTHOR__") {
			payload := strings.TrimPrefix(line, "__AUTHOR__")
			authorName, authorEmail, _ := strings.Cut(payload, "\x00")
			currentAuthor = contributorLabel(authorName, authorEmail)
			continue
		}
		if currentAuthor == "" || !strings.HasPrefix(line, "testcase/") {
			continue
		}
		relPath := strings.TrimPrefix(filepath.ToSlash(line), "testcase/")
		if _, exists := authorByRelPath[relPath]; !exists {
			authorByRelPath[relPath] = currentAuthor
		}
	}
	return authorByRelPath, nil
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
