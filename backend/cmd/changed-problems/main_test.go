package main

import (
	"bytes"
	"encoding/json"
	"os"
	"os/exec"
	"path"
	"path/filepath"
	"slices"
	"testing"
)

func TestSelectProblems(t *testing.T) {
	tests := []struct {
		name              string
		changedPaths      []string
		logicalToPhysical map[string]string
		problemDirs       map[string]bool
		wantAffected      []string
		wantUnowned       []string
	}{
		{
			name:         "nested KOI problem",
			changedPaths: []string{"testcase/koi/2026/1/elem/3/validator.cpp"},
			problemDirs:  map[string]bool{"testcase/koi/2026/1/elem/3": true},
			wantAffected: []string{"testcase/koi/2026/1/elem/3"},
		},
		{
			name:         "physical target and current consumer",
			changedPaths: []string{"testcase/boj/B/validator.cpp"},
			logicalToPhysical: map[string]string{
				"boj/B/validator.cpp": "boj/B/validator.cpp",
				"boj/A/validator.cpp": "boj/B/validator.cpp",
			},
			problemDirs: map[string]bool{
				"testcase/boj/A": true,
				"testcase/boj/B": true,
			},
			wantAffected: []string{"testcase/boj/A", "testcase/boj/B"},
		},
		{
			name:         "problem directory symlink",
			changedPaths: []string{"testcase/koi/2020/1/high/1"},
			problemDirs:  map[string]bool{"testcase/koi/2020/1/high/1": true},
			wantAffected: []string{"testcase/koi/2020/1/high/1"},
		},
		{
			name:         "deleted file in surviving problem",
			changedPaths: []string{"testcase/boj/1000/old.cpp"},
			problemDirs:  map[string]bool{"testcase/boj/1000": true},
			wantAffected: []string{"testcase/boj/1000"},
		},
		{
			name:         "entirely deleted problem",
			changedPaths: []string{"testcase/boj/1000/validator.cpp"},
			wantUnowned:  []string{"testcase/boj/1000/validator.cpp"},
		},
		{
			name:         "outside testcase",
			changedPaths: []string{"backend/main.go"},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			findProblemDirForPath := func(filePath string) (string, error) {
				if tt.problemDirs[filePath] {
					return filePath, nil
				}
				parent := path.Dir(filePath)
				if tt.problemDirs[parent] {
					return parent, nil
				}
				return "", nil
			}

			got, err := selectProblems(tt.changedPaths, tt.logicalToPhysical, findProblemDirForPath)
			if err != nil {
				t.Fatal(err)
			}
			if !slices.Equal(got.AffectedProblemDirs, nonNil(tt.wantAffected)) {
				t.Fatalf("affectedProblemDirs = %v, want %v", got.AffectedProblemDirs, tt.wantAffected)
			}
			if !slices.Equal(got.UnownedTestcasePaths, nonNil(tt.wantUnowned)) {
				t.Fatalf("unownedTestcasePaths = %v, want %v", got.UnownedTestcasePaths, tt.wantUnowned)
			}
		})
	}
}

func TestRun(t *testing.T) {
	repoRoot := t.TempDir()
	runGit(t, repoRoot, "init", "-q")
	writeFile(t, filepath.Join(repoRoot, "testcase", "boj", "B", "validator.cpp"), "base\n")
	consumerPath := filepath.Join(repoRoot, "testcase", "boj", "A", "validator.cpp")
	if err := os.MkdirAll(filepath.Dir(consumerPath), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.Symlink(filepath.Join("..", "B", "validator.cpp"), consumerPath); err != nil {
		t.Fatal(err)
	}
	commitAll(t, repoRoot, "base")
	base := runGit(t, repoRoot, "rev-parse", "HEAD")

	writeFile(t, filepath.Join(repoRoot, "testcase", "boj", "B", "validator.cpp"), "changed\n")
	commitAll(t, repoRoot, "change target")

	var output bytes.Buffer
	if err := run([]string{"--repo-root", repoRoot, "--base", base}, &output); err != nil {
		t.Fatal(err)
	}
	var got commandResult
	if err := json.Unmarshal(output.Bytes(), &got); err != nil {
		t.Fatal(err)
	}
	want := []string{"testcase/boj/A", "testcase/boj/B"}
	if !slices.Equal(got.AffectedProblemDirs, want) {
		t.Fatalf("affectedProblemDirs = %v, want %v", got.AffectedProblemDirs, want)
	}
	if got.UnownedTestcasePaths == nil || len(got.UnownedTestcasePaths) != 0 {
		t.Fatalf("unownedTestcasePaths = %v, want []", got.UnownedTestcasePaths)
	}
}

func nonNil(values []string) []string {
	if values == nil {
		return []string{}
	}
	return values
}

func writeFile(t *testing.T, filePath, content string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(filePath), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filePath, []byte(content), 0o644); err != nil {
		t.Fatal(err)
	}
}

func commitAll(t *testing.T, repoRoot, message string) {
	t.Helper()
	runGit(t, repoRoot, "add", "testcase")
	runGit(t, repoRoot, "-c", "user.name=Test", "-c", "user.email=test@example.com", "commit", "-q", "-m", message)
}

func runGit(t *testing.T, repoRoot string, args ...string) string {
	t.Helper()
	gitArgs := append([]string{"-C", repoRoot}, args...)
	output, err := exec.Command("git", gitArgs...).CombinedOutput()
	if err != nil {
		t.Fatalf("git %v: %v\n%s", args, err, output)
	}
	return string(bytes.TrimSpace(output))
}
