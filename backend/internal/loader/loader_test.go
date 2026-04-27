package loader

import (
	"os"
	"path/filepath"
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
