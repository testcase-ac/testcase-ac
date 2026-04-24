package main

import (
	"bytes"
	"encoding/json"
	"flag"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

func main() {
	repoRoot := flag.String("repo-root", "", "path to the repository root")
	outputPath := flag.String("output", "", "path to write the author index JSON")
	flag.Parse()

	if strings.TrimSpace(*repoRoot) == "" || strings.TrimSpace(*outputPath) == "" {
		fmt.Fprintln(os.Stderr, "usage: go run ./deploy/build-author-index.go -repo-root <repo-root> -output <output>")
		os.Exit(2)
	}

	authorByRelPath, err := buildAuthorIndex(*repoRoot)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	data, err := json.Marshal(authorByRelPath)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	if err := os.WriteFile(*outputPath, data, 0o644); err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}

func buildAuthorIndex(repoRoot string) (map[string]string, error) {
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
