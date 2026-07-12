package authorindex

import (
	"os"
	"os/exec"
	"path/filepath"
	"reflect"
	"strings"
	"testing"
)

func TestBuildUsesLatestAuthorForEachExactTestcasePath(t *testing.T) {
	repoRoot := newGitRepo(t)

	validatorPath := filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp")
	metadataPath := filepath.Join(repoRoot, "testcase", "boj", "1000", "metadata.yaml")
	writeFile(t, validatorPath, "int main() {}\n")
	writeFile(t, metadataPath, "title: A+B\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add problem")

	writeFile(t, validatorPath, "int main() { return 0; }\n")
	commitAll(t, repoRoot, "Carol", "123+carol@users.noreply.github.com", "update validator")

	index := mustBuild(t, repoRoot)

	if got := index["boj/1000/validator.cpp"]; got != "carol" {
		t.Fatalf("validator author = %q, want carol", got)
	}
	if got := index["boj/1000/metadata.yaml"]; got != "alice" {
		t.Fatalf("metadata author = %q, want alice", got)
	}
}

func TestWriteAndReadFileRoundTrip(t *testing.T) {
	path := filepath.Join(t.TempDir(), "author-index.json")
	want := map[string]string{
		"boj/1000/validator.cpp": "alice",
		"boj/1001/generator.cpp": "bob",
	}

	if err := WriteFile(path, want); err != nil {
		t.Fatal(err)
	}
	got, err := ReadFile(path)
	if err != nil {
		t.Fatal(err)
	}
	if !reflect.DeepEqual(got, want) {
		t.Fatalf("ReadFile() = %#v, want %#v", got, want)
	}
}

func TestBuildReturnsEmptyIndexWithoutGitRepository(t *testing.T) {
	index, err := Build(t.TempDir())
	if err != nil {
		t.Fatal(err)
	}
	if len(index) != 0 {
		t.Fatalf("len(Build()) = %d, want 0", len(index))
	}
}

func TestBuildCreditsFileSymlinkToDonorAuthor(t *testing.T) {
	repoRoot := newGitRepo(t)

	donorPath := filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp")
	writeFile(t, donorPath, "int main() {}\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add donor")

	consumerPath := filepath.Join(repoRoot, "testcase", "koi", "2025", "validator.cpp")
	symlink(t, filepath.Join("..", "..", "boj", "1000", "validator.cpp"), consumerPath)
	commitAll(t, repoRoot, "Bob", "bob@example.com", "link validator")

	index := mustBuild(t, repoRoot)
	if got := index["koi/2025/validator.cpp"]; got != "alice" {
		t.Fatalf("consumer author = %q, want alice", got)
	}
}

func TestBuildCreditsFileSymlinkToDonorMetadataOverrideInsteadOfLogicalOverride(t *testing.T) {
	repoRoot := newGitRepo(t)

	donorDir := filepath.Join(repoRoot, "testcase", "boj", "1000")
	donorPath := filepath.Join(donorDir, "validator.cpp")
	writeFile(t, donorPath, "int main() {}\n")
	writeFile(t, filepath.Join(donorDir, "metadata.yaml"), "title: Donor\nauthors:\n  validator.cpp: override-author\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add donor")

	consumerDir := filepath.Join(repoRoot, "testcase", "koi", "2025")
	consumerPath := filepath.Join(consumerDir, "validator.cpp")
	symlink(t, filepath.Join("..", "..", "boj", "1000", "validator.cpp"), consumerPath)
	writeFile(t, filepath.Join(consumerDir, "metadata.yaml"), "title: Consumer\nauthors:\n  validator.cpp: logical-override\n")
	commitAll(t, repoRoot, "Bob", "bob@example.com", "link validator")

	index := mustBuild(t, repoRoot)
	if got := index["koi/2025/validator.cpp"]; got != "override-author" {
		t.Fatalf("consumer author = %q, want donor metadata override", got)
	}
}

func TestBuildUsesMetadataOverridesWithoutGitRepository(t *testing.T) {
	repoRoot := t.TempDir()
	donorDir := filepath.Join(repoRoot, "testcase", "boj", "1000")
	writeFile(t, filepath.Join(donorDir, "validator.cpp"), "int main() {}\n")
	writeFile(t, filepath.Join(donorDir, "metadata.yaml"), "title: Donor\nauthors:\n  validator.cpp: override-author\n")
	symlink(
		t,
		filepath.Join("..", "..", "boj", "1000", "validator.cpp"),
		filepath.Join(repoRoot, "testcase", "koi", "2025", "validator.cpp"),
	)

	index := mustBuild(t, repoRoot)
	if got := index["koi/2025/validator.cpp"]; got != "override-author" {
		t.Fatalf("consumer author = %q, want donor metadata override", got)
	}
}

func TestBuildUsesInjectedDependencies(t *testing.T) {
	wantLogicalToPhysical := map[string]string{
		"koi/A/validator.cpp": "boj/B/validator.cpp",
		"koi/C/validator.cpp": "boj/B/validator.cpp",
	}

	index, err := buildWithDependencies("/repo", dependencies{
		loadLogicalToPhysical: func(string) (map[string]string, error) {
			return wantLogicalToPhysical, nil
		},
		loadGitAuthors: func(string) (map[string]string, error) {
			return map[string]string{"boj/B/validator.cpp": "git-author"}, nil
		},
		loadOverrides: func(_ string, physicalPaths []string) (map[string]string, error) {
			wantPhysicalPaths := []string{"boj/B/validator.cpp"}
			if !reflect.DeepEqual(physicalPaths, wantPhysicalPaths) {
				t.Fatalf("override loader paths = %v, want %v", physicalPaths, wantPhysicalPaths)
			}
			return map[string]string{"boj/B/validator.cpp": "override-author"}, nil
		},
	})
	if err != nil {
		t.Fatal(err)
	}

	want := map[string]string{
		"koi/A/validator.cpp": "override-author",
		"koi/C/validator.cpp": "override-author",
	}
	if !reflect.DeepEqual(index, want) {
		t.Fatalf("buildWithDependencies() = %v, want %v", index, want)
	}
}

func TestComposeAuthors(t *testing.T) {
	got := composeAuthors(
		map[string]string{
			"override.cpp": "override-target.cpp",
			"git.cpp":      "git-target.cpp",
			"alias.cpp":    "git-target.cpp",
			"missing.cpp":  "missing-target.cpp",
		},
		map[string]string{
			"override-target.cpp": "git-author",
			"git-target.cpp":      "git-author",
		},
		map[string]string{
			"override-target.cpp": "override-author",
			"git.cpp":             "ignored-logical-override",
		},
	)
	want := map[string]string{
		"override.cpp": "override-author",
		"git.cpp":      "git-author",
		"alias.cpp":    "git-author",
		"missing.cpp":  "",
	}
	if !reflect.DeepEqual(got, want) {
		t.Fatalf("composeAuthors() = %v, want %v", got, want)
	}
}

func TestBuildCreditsDirectoryAliasDescendantsToDonorAuthors(t *testing.T) {
	repoRoot := newGitRepo(t)

	donorDir := filepath.Join(repoRoot, "testcase", "koi", "2025", "elem")
	writeFile(t, filepath.Join(donorDir, "validator.cpp"), "int main() {}\n")
	writeFile(t, filepath.Join(donorDir, "generator.cpp"), "int main() {}\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add donor")

	aliasPath := filepath.Join(repoRoot, "testcase", "koi", "2025", "high")
	symlink(t, "elem", aliasPath)
	commitAll(t, repoRoot, "Bob", "bob@example.com", "add alias")

	index := mustBuild(t, repoRoot)
	for _, filename := range []string{"generator.cpp", "validator.cpp"} {
		key := "koi/2025/high/" + filename
		if got := index[key]; got != "alice" {
			t.Fatalf("%s author = %q, want alice", key, got)
		}
	}
}

func TestBuildRejectsAbsoluteSymlink(t *testing.T) {
	repoRoot := newGitRepo(t)

	donorPath := filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp")
	writeFile(t, donorPath, "int main() {}\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add donor")

	consumerPath := filepath.Join(repoRoot, "testcase", "koi", "2025", "validator.cpp")
	symlink(t, donorPath, consumerPath)
	commitAll(t, repoRoot, "Bob", "bob@example.com", "add absolute link")

	_, err := Build(repoRoot)
	if err == nil || !strings.Contains(err.Error(), "absolute testcase symlink") {
		t.Fatalf("Build() error = %v, want absolute testcase symlink error", err)
	}
}

func TestBuildRejectsFileSymlinkCycle(t *testing.T) {
	repoRoot := newGitRepo(t)

	problemDir := filepath.Join(repoRoot, "testcase", "boj", "1000")
	symlink(t, "generator.cpp", filepath.Join(problemDir, "validator.cpp"))
	symlink(t, "validator.cpp", filepath.Join(problemDir, "generator.cpp"))
	commitAll(t, repoRoot, "Bob", "bob@example.com", "add cycle")

	_, err := Build(repoRoot)
	if err == nil || !strings.Contains(err.Error(), "cyclic testcase symlink") {
		t.Fatalf("Build() error = %v, want cyclic testcase symlink error", err)
	}
}

func TestBuildFollowsChainedLinksAfterDonorChanges(t *testing.T) {
	repoRoot := newGitRepo(t)

	donorPath := filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp")
	writeFile(t, donorPath, "int main() {}\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add donor")

	sharedPath := filepath.Join(repoRoot, "testcase", "shared", "validator.cpp")
	symlink(t, filepath.Join("..", "boj", "1000", "validator.cpp"), sharedPath)
	aliasPath := filepath.Join(repoRoot, "testcase", "koi", "2025")
	symlink(t, filepath.Join("..", "shared"), aliasPath)
	commitAll(t, repoRoot, "Bob", "bob@example.com", "add chained consumers")

	index := mustBuild(t, repoRoot)
	if got := index["koi/2025/validator.cpp"]; got != "alice" {
		t.Fatalf("initial consumer author = %q, want alice", got)
	}

	writeFile(t, donorPath, "int main() { return 0; }\n")
	commitAll(t, repoRoot, "Carol", "carol@example.com", "update donor")
	index = mustBuild(t, repoRoot)
	if got := index["koi/2025/validator.cpp"]; got != "carol" {
		t.Fatalf("updated consumer author = %q, want carol", got)
	}
}

func TestBuildOmitsDeletedHistoricalPaths(t *testing.T) {
	repoRoot := newGitRepo(t)
	deletedPath := filepath.Join(repoRoot, "testcase", "boj", "1000", "deleted.cpp")
	writeFile(t, deletedPath, "int main() {}\n")
	writeFile(t, filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp"), "int main() {}\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add problem")

	if err := os.Remove(deletedPath); err != nil {
		t.Fatal(err)
	}
	commitAll(t, repoRoot, "Bob", "bob@example.com", "remove obsolete file")

	index := mustBuild(t, repoRoot)
	if _, exists := index["boj/1000/deleted.cpp"]; exists {
		t.Fatal("deleted historical path remains in current logical index")
	}
}

func TestBuildKeepsCurrentUntrackedFilesWithEmptyAuthor(t *testing.T) {
	repoRoot := newGitRepo(t)
	writeFile(t, filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp"), "int main() {}\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add problem")
	writeFile(t, filepath.Join(repoRoot, "testcase", "boj", "1000", "generator.cpp"), "int main() {}\n")

	index := mustBuild(t, repoRoot)
	author, exists := index["boj/1000/generator.cpp"]
	if !exists || author != "" {
		t.Fatalf("untracked file entry = (%q, %t), want empty author and present key", author, exists)
	}
}

func TestBuildLeavesRecreatedUntrackedPathUnattributed(t *testing.T) {
	repoRoot := newGitRepo(t)
	path := filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp")
	writeFile(t, path, "original\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add file")

	if err := os.Remove(path); err != nil {
		t.Fatal(err)
	}
	commitAll(t, repoRoot, "Bob", "bob@example.com", "delete file")
	writeFile(t, path, "untracked replacement\n")

	index := mustBuild(t, repoRoot)
	author, exists := index["boj/1000/validator.cpp"]
	if !exists || author != "" {
		t.Fatalf("recreated file entry = (%q, %t), want empty author and present key", author, exists)
	}
}

func TestBuildRejectsBrokenSymlink(t *testing.T) {
	repoRoot := newGitRepo(t)
	symlink(t, "missing.cpp", filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp"))
	commitAll(t, repoRoot, "Bob", "bob@example.com", "add broken link")

	if _, err := Build(repoRoot); err == nil {
		t.Fatal("Build() succeeded, want broken symlink error")
	}
}

func TestBuildRejectsSymlinkLeavingTestcase(t *testing.T) {
	repoRoot := newGitRepo(t)
	writeFile(t, filepath.Join(repoRoot, "outside.cpp"), "int main() {}\n")
	symlink(t, filepath.Join("..", "..", "..", "outside.cpp"), filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp"))
	commitAll(t, repoRoot, "Bob", "bob@example.com", "add escaping link")

	_, err := Build(repoRoot)
	if err == nil || !strings.Contains(err.Error(), "target leaves testcase") {
		t.Fatalf("Build() error = %v, want target leaves testcase error", err)
	}
}

func TestBuildRejectsDirectoryAliasCycle(t *testing.T) {
	repoRoot := newGitRepo(t)
	symlink(t, "..", filepath.Join(repoRoot, "testcase", "koi", "loop"))
	commitAll(t, repoRoot, "Bob", "bob@example.com", "add directory cycle")

	_, err := Build(repoRoot)
	if err == nil || !strings.Contains(err.Error(), "cyclic testcase directory symlink") {
		t.Fatalf("Build() error = %v, want cyclic testcase directory symlink error", err)
	}
}

func newGitRepo(t *testing.T) string {
	t.Helper()
	repoRoot := t.TempDir()
	runGit(t, repoRoot, "init", "-q")
	return repoRoot
}

func mustBuild(t *testing.T, repoRoot string) map[string]string {
	t.Helper()
	index, err := Build(repoRoot)
	if err != nil {
		t.Fatal(err)
	}
	return index
}

func writeFile(t *testing.T, path, content string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, []byte(content), 0o644); err != nil {
		t.Fatal(err)
	}
}

func symlink(t *testing.T, target, path string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.Symlink(target, path); err != nil {
		t.Fatal(err)
	}
}

func commitAll(t *testing.T, repoRoot, authorName, authorEmail, message string) {
	t.Helper()
	runGit(t, repoRoot, "add", "testcase")
	cmd := exec.Command(
		"git", "-C", repoRoot,
		"-c", "user.name="+authorName,
		"-c", "user.email="+authorEmail,
		"commit", "-q", "-m", message,
	)
	if output, err := cmd.CombinedOutput(); err != nil {
		t.Fatalf("git commit: %v\n%s", err, output)
	}
}

func runGit(t *testing.T, repoRoot string, args ...string) string {
	t.Helper()
	cmdArgs := append([]string{"-C", repoRoot}, args...)
	output, err := exec.Command("git", cmdArgs...).CombinedOutput()
	if err != nil {
		t.Fatalf("git %v: %v\n%s", args, err, output)
	}
	return string(output)
}
