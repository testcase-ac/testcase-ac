package authorindex

import (
	"os"
	"os/exec"
	"path/filepath"
	"reflect"
	"testing"
)

func TestBuildUsesLatestAuthorForEachExactTestcasePath(t *testing.T) {
	repoRoot := t.TempDir()
	runGit(t, repoRoot, "init", "-q")

	validatorPath := filepath.Join(repoRoot, "testcase", "boj", "1000", "validator.cpp")
	metadataPath := filepath.Join(repoRoot, "testcase", "boj", "1000", "metadata.yaml")
	writeFile(t, validatorPath, "int main() {}\n")
	writeFile(t, metadataPath, "title: A+B\n")
	commitAll(t, repoRoot, "Alice", "alice@example.com", "add problem")

	writeFile(t, validatorPath, "int main() { return 0; }\n")
	commitAll(t, repoRoot, "Carol", "123+carol@users.noreply.github.com", "update validator")

	index, err := Build(repoRoot)
	if err != nil {
		t.Fatal(err)
	}

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

func writeFile(t *testing.T, path, content string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, []byte(content), 0o644); err != nil {
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
