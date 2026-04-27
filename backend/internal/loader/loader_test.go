package loader

import (
	"os"
	"path/filepath"
	"sort"
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestLoadProblemRejectsUnknownMetadataField(t *testing.T) {
	dir := t.TempDir()
	problemDir := filepath.Join(dir, "boj", "1000")
	if err := os.MkdirAll(problemDir, 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(problemDir, "metadata.yaml"), []byte("title: A+B\nunknown: true\n"), 0o644); err != nil {
		t.Fatal(err)
	}
	if _, err := LoadProblem(problemDir, Options{}); err == nil {
		t.Fatalf("LoadProblem() succeeded with unknown metadata field")
	}
}

func TestLoadProblemRejectsDirectoryWideAuthor(t *testing.T) {
	dir := t.TempDir()
	problemDir := filepath.Join(dir, "koi", "2019", "1", "elem", "1")
	if err := os.MkdirAll(problemDir, 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(problemDir, "metadata.yaml"), []byte("title: A+B\nauthor: 한국정보올림피아드\n"), 0o644); err != nil {
		t.Fatal(err)
	}
	if _, err := LoadProblem(problemDir, Options{}); err == nil {
		t.Fatalf("LoadProblem() succeeded with directory-wide author")
	}
}

func TestLoadProblemMetadataAuthorsOverrideGitAuthorByFilename(t *testing.T) {
	dir := t.TempDir()
	problemDir := filepath.Join(dir, "koi", "2019", "1", "elem", "1")
	if err := os.MkdirAll(problemDir, 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(problemDir, "metadata.yaml"), []byte("title: A+B\nauthors:\n  correct_reference.cpp: 한국정보올림피아드\n"), 0o644); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(problemDir, "correct_reference.cpp"), []byte("int main(){}\n"), 0o644); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(problemDir, "generator_1.cpp"), []byte("int main(){}\n"), 0o644); err != nil {
		t.Fatal(err)
	}

	problem, err := LoadProblem(problemDir, Options{
		ProblemType: "koi",
		ExternalID:  "2019/1/elem/1",
		AuthorByRelPath: map[string]string{
			"koi/2019/1/elem/1/correct_reference.cpp": "git-author",
			"koi/2019/1/elem/1/generator_1.cpp":       "generator-author",
		},
	})
	if err != nil {
		t.Fatal(err)
	}
	if len(problem.CorrectCodes) != 1 {
		t.Fatalf("len(CorrectCodes) = %d, want 1", len(problem.CorrectCodes))
	}
	if got := problem.CorrectCodes[0].AuthorName; got != "한국정보올림피아드" {
		t.Fatalf("CorrectCodes[0].AuthorName = %q, want metadata authors override", got)
	}
	if len(problem.Generators) != 1 {
		t.Fatalf("len(Generators) = %d, want 1", len(problem.Generators))
	}
	if got := problem.Generators[0].AuthorName; got != "generator-author" {
		t.Fatalf("Generators[0].AuthorName = %q, want git author", got)
	}
}

func TestBuildCatalogFindsNestedProblemsAndSymlinkDirs(t *testing.T) {
	dir := t.TempDir()
	testcaseRoot := filepath.Join(dir, "testcase")
	realProblemDir := filepath.Join(testcaseRoot, "koi", "2020", "1", "elem", "1")
	if err := os.MkdirAll(realProblemDir, 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(realProblemDir, "metadata.yaml"), []byte("title: Shared\n"), 0o644); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(realProblemDir, "correct_reference.cpp"), []byte("int main(){}\n"), 0o644); err != nil {
		t.Fatal(err)
	}
	linkParent := filepath.Join(testcaseRoot, "koi", "2020", "1", "high")
	if err := os.MkdirAll(linkParent, 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.Symlink(filepath.Join("..", "elem", "1"), filepath.Join(linkParent, "1")); err != nil {
		t.Fatal(err)
	}

	catalog, err := BuildCatalog(testcaseRoot)
	if err != nil {
		t.Fatal(err)
	}
	gotIDs := make([]string, 0, len(catalog))
	for key := range catalog {
		if key[0] == "koi" {
			gotIDs = append(gotIDs, key[1])
		}
	}
	sort.Strings(gotIDs)
	wantIDs := []string{"2020/1/elem/1", "2020/1/high/1"}
	if len(gotIDs) != len(wantIDs) {
		t.Fatalf("koi ids = %v, want %v", gotIDs, wantIDs)
	}
	for i := range wantIDs {
		if gotIDs[i] != wantIDs[i] {
			t.Fatalf("koi ids = %v, want %v", gotIDs, wantIDs)
		}
	}
	if got := catalog[[2]string{"koi", "2020/1/high/1"}].Title; got != "Shared" {
		t.Fatalf("symlinked problem title = %q, want Shared", got)
	}
}

func TestLoadTypeMetadataPreservesOrderedLabels(t *testing.T) {
	dir := t.TempDir()
	typeDir := filepath.Join(dir, "koi")
	if err := os.MkdirAll(typeDir, 0o755); err != nil {
		t.Fatal(err)
	}
	content := []byte(`schemaVersion: 1
label: KOI
segments:
  - label: "{}년"
  - label: "{}차대회"
  - labels:
      elem: "초등부"
      mid: "중등부"
      high: "고등부"
  - label: "{}번"
`)
	if err := os.WriteFile(filepath.Join(typeDir, typeMetadataName), content, 0o644); err != nil {
		t.Fatal(err)
	}

	metadata, err := LoadTypeMetadata(typeDir)
	if err != nil {
		t.Fatal(err)
	}
	if metadata == nil {
		t.Fatal("LoadTypeMetadata() = nil, want metadata")
	}
	if metadata.Label != "KOI" {
		t.Fatalf("Label = %q, want KOI", metadata.Label)
	}
	if got := metadata.Segments[0].Label; got != "{}년" {
		t.Fatalf("first segment label = %q, want {}년", got)
	}
	labels := metadata.Segments[2].Labels
	wantValues := []string{"elem", "mid", "high"}
	if len(labels) != len(wantValues) {
		t.Fatalf("labels = %#v, want %v", labels, wantValues)
	}
	for i, want := range wantValues {
		if labels[i].Value != want {
			t.Fatalf("label order = %#v, want %v", labels, wantValues)
		}
	}
}

func TestLoadProblemInfersAndSortsFiles(t *testing.T) {
	dir := t.TempDir()
	problemDir := filepath.Join(dir, "boj", "1000")
	if err := os.MkdirAll(problemDir, 0o755); err != nil {
		t.Fatal(err)
	}
	files := map[string]string{
		"metadata.yaml":       "title: A+B\ncodes:\n  correct_slow.cpp: cpp14\n",
		"correct.cpp":         "int main(){}",
		"correct_slow.cpp":    "int main(){}",
		"correct_fast.js":     "console.log(0)",
		"generator.py":        "print('1 2')",
		"generator_random.js": "console.log('1 2')",
		"singlegen.py":        "print('1 2')",
		"singlegen_edge.js":   "console.log('1 2')",
		"testcase.txt":        "1 2\n",
		"testcase_sample.txt": "1 2\n",
	}
	for name, content := range files {
		if err := os.WriteFile(filepath.Join(problemDir, name), []byte(content), 0o644); err != nil {
			t.Fatal(err)
		}
	}
	problem, err := LoadProblem(problemDir, Options{})
	if err != nil {
		t.Fatal(err)
	}
	if got := problem.CorrectCodes[0].Filename; got != "correct.cpp" {
		t.Fatalf("first correct file = %q, want sorted correct.cpp", got)
	}
	if got := problem.CorrectCodes[2].Language; got != contracts.LanguageCpp14 {
		t.Fatalf("override language = %q, want cpp14", got)
	}
	if len(problem.CorrectCodes) != 3 || len(problem.Generators) != 2 || len(problem.Singlegens) != 2 || len(problem.Testcases) != 2 {
		t.Fatalf("loaded problem counts = correct:%d generator:%d singlegen:%d testcase:%d", len(problem.CorrectCodes), len(problem.Generators), len(problem.Singlegens), len(problem.Testcases))
	}
}
