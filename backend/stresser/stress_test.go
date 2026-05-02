package main

import (
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func textProvider(id, content string) contracts.CaseProvider {
	return contracts.CaseProvider{
		Type:    contracts.CaseProviderText,
		ID:      id,
		Content: content,
	}
}

func generatorProvider(id string, language contracts.Language, code string) contracts.CaseProvider {
	return contracts.CaseProvider{
		Type:     contracts.CaseProviderGenerator,
		ID:       id,
		Code:     code,
		Language: language,
	}
}

func singlegenProvider(id string, language contracts.Language, code string) contracts.CaseProvider {
	return contracts.CaseProvider{
		Type:     contracts.CaseProviderSinglegen,
		ID:       id,
		Code:     code,
		Language: language,
	}
}

func testCheckerCode() string {
	return `#include "testlib.h"
#include <cmath>

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    double p = 0.0;
    double j = 0.0;
    p = ouf.readDouble();
    j = ans.readDouble();

    if (std::fabs(p - j) <= 1e-6) {
        quitf(_ok, "accepted");
    }

    quitf(_wa, "expected %.10f got %.10f", j, p);
}
`
}

func TestOperationStressSmoke(t *testing.T) {
	requireCommands(t, "g++")

	program := `#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << a + b << "\n";
    return 0;
}
`
	singlegen := `#include <iostream>

int main() {
    std::cout << "1 2\n";
    return 0;
}
`

	result, err := operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         program,
		TargetCodeLang:     contracts.LanguageCpp23,
		CorrectCode:        program,
		CorrectCodeLang:    contracts.LanguageCpp23,
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         1,
		CaseProviders: []contracts.CaseProvider{
			singlegenProvider("sg-1", contracts.LanguageCpp23, singlegen),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 1 {
		t.Fatalf("TotalCases = %d, want 1", result.TotalCases)
	}
	if result.CorrectCasesCount != 1 {
		t.Fatalf("CorrectCasesCount = %d, want 1", result.CorrectCasesCount)
	}
	if result.WrongCasesCount != 0 {
		t.Fatalf("WrongCasesCount = %d, want 0", result.WrongCasesCount)
	}
	if result.ExecutionFailedCasesCount != 0 {
		t.Fatalf("ExecutionFailedCasesCount = %d, want 0", result.ExecutionFailedCasesCount)
	}
}

func TestOperationStressFindsCounterexample(t *testing.T) {
	requireCommands(t, "g++")

	targetCode := `#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    if (a == 3) {
        cout << a - b << "\n";
    } else {
        cout << a + b << "\n";
    }
    return 0;
}
`
	correctCode := `#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << a + b << "\n";
    return 0;
}
`
	generatorCode := `#include <iostream>
#include <random>
#include <string>

int main(int argc, char* argv[]) {
    int seed = argc > 1 ? std::stoi(argv[1]) : 42;
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 9);
    std::cout << dist(rng) << " " << dist(rng) << "\n";
    return 0;
}
`

	result, err := operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         targetCode,
		TargetCodeLang:     "cpp23",
		CorrectCode:        correctCode,
		CorrectCodeLang:    "cpp23",
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         20,
		CaseProviders: []contracts.CaseProvider{
			textProvider("tc-1", "1 2"),
			textProvider("tc-2", "1 1"),
			textProvider("tc-3", "3 7"),
			textProvider("tc-4", "10 9"),
			generatorProvider("gen-1", "cpp23", generatorCode),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 20 {
		t.Fatalf("TotalCases = %d, want 20", result.TotalCases)
	}
	if result.WrongCasesCount == 0 {
		t.Fatalf("WrongCasesCount = 0, want > 0")
	}
	if len(result.WrongCases) == 0 {
		t.Fatalf("WrongCases was empty")
	}
}

func TestOperationStressSurfaceRuntimeErrorVerdict(t *testing.T) {
	requireCommands(t, python313Command, "g++")

	targetCode := `raise RuntimeError("boom")`
	correctCode := `#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << a + b << "\n";
    return 0;
}
`
	generatorCode := `#include <iostream>
int main() {
    std::cout << "1 2\n";
    return 0;
}
`

	result, err := operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         targetCode,
		TargetCodeLang:     "python3",
		CorrectCode:        correctCode,
		CorrectCodeLang:    "cpp23",
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         10,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-rte", "cpp23", generatorCode),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 10 {
		t.Fatalf("TotalCases = %d, want 10", result.TotalCases)
	}
	if result.WrongCasesCount != 0 {
		t.Fatalf("WrongCasesCount = %d, want 0", result.WrongCasesCount)
	}
	if result.ExecutionFailedCasesCount != 10 {
		t.Fatalf("ExecutionFailedCasesCount = %d, want 10", result.ExecutionFailedCasesCount)
	}
	if len(result.ExecutionFailedCases) == 0 {
		t.Fatalf("ExecutionFailedCases was empty")
	}
	for _, failedCase := range result.ExecutionFailedCases {
		if failedCase.Reason != contracts.VerdictRuntimeError {
			t.Fatalf("execution failed reason = %q, want RTE", failedCase.Reason)
		}
		if failedCase.Stderr == nil || failedCase.Stderr.Text == "" {
			t.Fatalf("expected stderr for runtime error failure: %+v", failedCase)
		}
	}
}

func TestOperationStressCheckerMismatch(t *testing.T) {
	requireCommands(t, python313Command, "g++")

	targetCode := `a, b = map(int, input().split())
print(a // b)
`
	correctCode := `a, b = map(int, input().split())
print(a / b)
`
	generatorCode := `#include <iostream>
#include <random>
#include <string>

int main(int argc, char* argv[]) {
    int seed = argc > 1 ? std::stoi(argv[1]) : 42;
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 9);
    int a = dist(rng);
    int b = dist(rng);
    if (b == 0) b = 1;
    std::cout << a << " " << b << "\n";
    return 0;
}
`

	result, err := operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         targetCode,
		TargetCodeLang:     "python3",
		CorrectCode:        correctCode,
		CorrectCodeLang:    "python3",
		CheckerCode:        testCheckerCode(),
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         20,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-checker", "cpp23", generatorCode),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 20 {
		t.Fatalf("TotalCases = %d, want 20", result.TotalCases)
	}
	if result.WrongCasesCount == 0 {
		t.Fatalf("WrongCasesCount = 0, want > 0")
	}
	foundCheckerOutput := false
	for _, wrongCase := range result.WrongCases {
		if wrongCase.Stderr != nil {
			t.Fatalf("wrong case stderr = %+v, want empty submitted-code stderr", wrongCase.Stderr)
		}
		if wrongCase.CheckerOutput != nil && wrongCase.CheckerOutput.Text != "" {
			foundCheckerOutput = true
			break
		}
	}
	if !foundCheckerOutput {
		t.Fatalf("expected checker output in at least one counterexample: %+v", result.WrongCases)
	}
}

func TestOperationStressDetectsNullCharacterDifference(t *testing.T) {
	requireCommands(t, "gcc")

	generatorCode := `#include <stdio.h>

int main() {
    printf("3 7\n");
    return 0;
}
`
	correctCode := `#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", a + b);
    return 0;
}
`
	targetCode := `#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", a + b);
    putchar('\0');
    return 0;
}
`

	result, err := operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         targetCode,
		TargetCodeLang:     "c11",
		CorrectCode:        correctCode,
		CorrectCodeLang:    "c11",
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         10,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-null", "c11", generatorCode),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 10 {
		t.Fatalf("TotalCases = %d, want 10", result.TotalCases)
	}
	if result.WrongCasesCount != 10 {
		t.Fatalf("WrongCasesCount = %d, want 10", result.WrongCasesCount)
	}
	for _, wrongCase := range result.WrongCases {
		if wrongCase.Verdict == nil || *wrongCase.Verdict != contracts.VerdictWrongAnswer {
			t.Fatalf("counterexample verdict = %v, want WA", wrongCase.Verdict)
		}
	}
}

func TestOperationStressUsesMultipleGenerators(t *testing.T) {
	requireCommands(t, "gcc")

	generator1Code := `#include <stdio.h>
int main() {
    printf("1 1\n");
    return 0;
}
`
	generator2Code := `#include <stdio.h>
int main() {
    printf("2 2\n");
    return 0;
}
`
	targetCode := `#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a == 1) {
        a--;
    }
    printf("%d\n", a + b);
    return 0;
}
`
	correctCode := `#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", a + b);
    return 0;
}
`

	result, err := operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         targetCode,
		TargetCodeLang:     "c11",
		CorrectCode:        correctCode,
		CorrectCodeLang:    "c11",
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         40,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-1", "c11", generator1Code),
			generatorProvider("gen-2", "c11", generator2Code),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 40 {
		t.Fatalf("TotalCases = %d, want 40", result.TotalCases)
	}
	if result.WrongCasesCount == 0 {
		t.Fatalf("WrongCasesCount = 0, want > 0")
	}
	if result.CorrectCasesCount == 0 {
		t.Fatalf("CorrectCasesCount = 0, want > 0")
	}
}

func TestOperationStressSkipsFailingGenerator(t *testing.T) {
	requireCommands(t, "gcc")

	failingGeneratorCode := `#include <stdlib.h>
int main() {
    return 1;
}
`
	successfulGeneratorCode := `#include <stdio.h>
int main() {
    printf("2 2\n");
    return 0;
}
`
	targetCode := `#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", a + b);
    return 0;
}
`

	result, err := operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         targetCode,
		TargetCodeLang:     "c11",
		CorrectCode:        targetCode,
		CorrectCodeLang:    "c11",
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         50,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-bad", "c11", failingGeneratorCode),
			generatorProvider("gen-good", "c11", successfulGeneratorCode),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases >= 50 {
		t.Fatalf("TotalCases = %d, want < 50 to reflect skipped failing generator iterations", result.TotalCases)
	}
	if result.TotalCases < 40 {
		t.Fatalf("TotalCases = %d, want >= 40 so the healthy generator still dominates after failures", result.TotalCases)
	}
	if result.WrongCasesCount != 0 {
		t.Fatalf("WrongCasesCount = %d, want 0", result.WrongCasesCount)
	}
	if result.CorrectCasesCount != result.TotalCases {
		t.Fatalf("CorrectCasesCount = %d, want %d", result.CorrectCasesCount, result.TotalCases)
	}
}

func TestBuildStressResponseDedupsAndLimitsReturnedFailures(t *testing.T) {
	wrongCases := []stressIteration{
		{
			Testcase:      "9 9\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g3"},
			CorrectOutput: "18\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictWrongAnswer,
				TargetOutput: "0\n",
			},
		},
		{
			Testcase:      "1 1\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g1"},
			CorrectOutput: "2\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictWrongAnswer,
				TargetOutput: "0\n",
			},
		},
		{
			Testcase:      "1 1",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g1-dup"},
			CorrectOutput: "2\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictWrongAnswer,
				TargetOutput: "1\n",
			},
		},
	}
	executionFailedCases := []stressIteration{
		{
			Testcase:      "2 2\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g2"},
			CorrectOutput: "4\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictRuntimeError,
				TargetOutput: "",
				Stderr:       "boom",
			},
		},
		{
			Testcase:      "3 3\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g4"},
			CorrectOutput: "6\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictTimeLimit,
				TargetOutput: "",
			},
		},
	}
	correctCases := []stressIteration{
		{
			Testcase:    "4 4\n",
			GeneratedBy: contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g5"},
		},
	}

	result := buildStressResponse(wrongCases, executionFailedCases, correctCases, false)
	if result.TotalCases != 6 {
		t.Fatalf("TotalCases = %d, want 6", result.TotalCases)
	}
	if result.WrongCasesCount != 3 {
		t.Fatalf("WrongCasesCount = %d, want 3", result.WrongCasesCount)
	}
	if result.ExecutionFailedCasesCount != 2 {
		t.Fatalf("ExecutionFailedCasesCount = %d, want 2", result.ExecutionFailedCasesCount)
	}
	if result.CorrectCasesCount != 1 {
		t.Fatalf("CorrectCasesCount = %d, want 1", result.CorrectCasesCount)
	}
	if len(result.WrongCases) != 2 {
		t.Fatalf("len(WrongCases) = %d, want 2", len(result.WrongCases))
	}
	if len(result.ExecutionFailedCases) != 2 {
		t.Fatalf("len(ExecutionFailedCases) = %d, want 2", len(result.ExecutionFailedCases))
	}

	gotWrongTestcases := []string{
		result.WrongCases[0].Testcase.Text,
		result.WrongCases[1].Testcase.Text,
	}
	wantWrongTestcases := []string{"1 1\n", "9 9\n"}
	for i := range wantWrongTestcases {
		if gotWrongTestcases[i] != wantWrongTestcases[i] {
			t.Fatalf("WrongCases[%d].Testcase.Text = %q, want %q", i, gotWrongTestcases[i], wantWrongTestcases[i])
		}
	}

	gotFailedTestcases := []string{
		result.ExecutionFailedCases[0].Testcase.Text,
		result.ExecutionFailedCases[1].Testcase.Text,
	}
	wantFailedTestcases := []string{"2 2\n", "3 3\n"}
	for i := range wantFailedTestcases {
		if gotFailedTestcases[i] != wantFailedTestcases[i] {
			t.Fatalf("ExecutionFailedCases[%d].Testcase.Text = %q, want %q", i, gotFailedTestcases[i], wantFailedTestcases[i])
		}
	}
}
