package verify

import (
	"context"
	"os"
	"os/exec"
	"path/filepath"
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
)

func TestValidPythonProblemPasses(t *testing.T) {
	requirePython(t)
	problem := loadFixtureProblem(t, map[string]string{
		"metadata.yaml": "title: Valid\n",
		"correct_main.py": `
a, b = map(int, input().split())
print(a + b)
`,
		"generator_seeded.py": `
import sys

seed = int(sys.argv[1])
print((seed % 50) + 1, 2)
`,
	})
	report := VerifyProblem(context.Background(), problem)
	if report.Status != StatusOK {
		t.Fatalf("status = %s, findings = %+v", report.Status, report.Findings)
	}
	if report.SampledCasesCount != GeneratorRuns {
		t.Fatalf("sample count = %d, want %d", report.SampledCasesCount, GeneratorRuns)
	}
}

func TestGeneratorIgnoringSeedFails(t *testing.T) {
	requirePython(t)
	problem := loadFixtureProblem(t, map[string]string{
		"metadata.yaml": "title: Constant Generator\n",
		"correct_main.py": `
a, b = map(int, input().split())
print(a + b)
`,
		"generator_constant.py": `print("1 2")`,
	})
	report := VerifyProblem(context.Background(), problem)
	if !hasFinding(report, SeverityError, StageGenerator, "generator_constant.py") {
		t.Fatalf("expected generator finding, got %+v", report.Findings)
	}
}

func TestCorrectMismatchFails(t *testing.T) {
	requirePython(t)
	problem := loadFixtureProblem(t, map[string]string{
		"metadata.yaml":       "title: Mismatch\n",
		"testcase_sample.txt": "7 3\n",
		"correct_add.py": `
a, b = map(int, input().split())
print(a + b)
`,
		"correct_subtract.py": `
a, b = map(int, input().split())
print(a - b)
`,
	})
	report := VerifyProblem(context.Background(), problem)
	if !hasFinding(report, SeverityError, StageCorrectConsistency, "correct_subtract.py") {
		t.Fatalf("expected correct consistency finding, got %+v", report.Findings)
	}
}

func TestSingleCorrectFailureFails(t *testing.T) {
	requirePython(t)
	problem := loadFixtureProblem(t, map[string]string{
		"metadata.yaml":       "title: Single Correct Failure\n",
		"testcase_sample.txt": "7 3\n",
		"correct_main.py": `
raise RuntimeError("boom")
`,
	})
	report := VerifyProblem(context.Background(), problem)
	if report.Status != StatusFailed {
		t.Fatalf("status = %s, findings = %+v", report.Status, report.Findings)
	}
	if !hasFinding(report, SeverityError, StageCorrectConsistency, "correct_main.py") {
		t.Fatalf("expected correct execution finding, got %+v", report.Findings)
	}
}

func TestMissingCorrectWarnsAndSkips(t *testing.T) {
	requirePython(t)
	problem := loadFixtureProblem(t, map[string]string{
		"metadata.yaml": "title: Missing Correct\n",
		"generator_seeded.py": `
import sys

seed = int(sys.argv[1])
print((seed % 50) + 1, 2)
`,
	})
	report := VerifyProblem(context.Background(), problem)
	if report.Status != StatusOK {
		t.Fatalf("status = %s, findings = %+v", report.Status, report.Findings)
	}
	if !hasFinding(report, SeverityWarning, StageStatic, "") {
		t.Fatalf("expected missing correct warning, got %+v", report.Findings)
	}
}

func loadFixtureProblem(t *testing.T, files map[string]string) loader.Problem {
	t.Helper()
	root := t.TempDir()
	problemDir := filepath.Join(root, "boj", "1")
	if err := os.MkdirAll(problemDir, 0o755); err != nil {
		t.Fatal(err)
	}
	for name, content := range files {
		if err := os.WriteFile(filepath.Join(problemDir, name), []byte(content), 0o644); err != nil {
			t.Fatal(err)
		}
	}
	problem, err := loader.LoadProblem(problemDir, loader.Options{})
	if err != nil {
		t.Fatal(err)
	}
	return problem
}

func hasFinding(report VerifyReport, severity Severity, stage Stage, filename string) bool {
	for _, finding := range report.Findings {
		if finding.Severity == severity && finding.Stage == stage && finding.Filename == filename {
			return true
		}
	}
	return false
}

func requirePython(t *testing.T) {
	t.Helper()
	if _, err := exec.LookPath(executor.Python313Command); err != nil {
		t.Skipf("%s is required for verify tests", executor.Python313Command)
	}
}
