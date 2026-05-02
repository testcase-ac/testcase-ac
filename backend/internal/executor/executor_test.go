package executor

import (
	"context"
	"fmt"
	"os"
	"os/exec"
	"sort"
	"strings"
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestMain(m *testing.M) {
	if missing := missingExecutorRuntimePrerequisites(); len(missing) > 0 {
		fmt.Fprintf(os.Stderr, "missing executor runtime prerequisites:\n")
		for _, item := range missing {
			fmt.Fprintf(os.Stderr, "  - %s\n", item)
		}
		fmt.Fprintf(os.Stderr, "run ./tests/dockertest/run_test.sh ./internal/executor for the Docker-backed executor test environment\n")
		os.Exit(1)
	}
	os.Exit(m.Run())
}

func missingExecutorRuntimePrerequisites() []string {
	requiredCommands := map[string]struct{}{}
	requiredPaths := map[string]struct{}{
		"/var/task/CsharpApp/obj/project.assets.json": {},
	}
	for _, smokeCase := range supportedLanguageSmokeCases() {
		for _, name := range smokeCase.RequiredExecutables {
			requiredCommands[name] = struct{}{}
		}
		for _, path := range smokeCase.RequiredPaths {
			requiredPaths[path] = struct{}{}
		}
	}

	missing := []string{}
	for name := range requiredCommands {
		if _, err := exec.LookPath(name); err != nil {
			missing = append(missing, fmt.Sprintf("command %q", name))
		}
	}
	for path := range requiredPaths {
		if _, err := os.Stat(path); err != nil {
			missing = append(missing, fmt.Sprintf("path %q", path))
		}
	}
	cmd := exec.Command("bash", "-lc", "ulimit -v 65536")
	if output, err := cmd.CombinedOutput(); err != nil {
		detail := strings.TrimSpace(string(output))
		if detail == "" {
			detail = err.Error()
		}
		missing = append(missing, fmt.Sprintf("Linux-style virtual memory limits for MLE tests (%s)", detail))
	}
	sort.Strings(missing)
	return missing
}

func requireCommands(t *testing.T, names ...string) {
	t.Helper()
	for _, name := range names {
		if _, err := exec.LookPath(name); err != nil {
			t.Fatalf("required command %q is not available; run ./tests/dockertest/run_test.sh ./internal/executor for the Docker-backed executor test environment", name)
		}
	}
}

func requirePaths(t *testing.T, paths ...string) {
	t.Helper()
	for _, path := range paths {
		if _, err := os.Stat(path); err != nil {
			t.Fatalf("required path %q is not available; run ./tests/dockertest/run_test.sh ./internal/executor for the Docker-backed executor test environment", path)
		}
	}
}

func requireVirtualMemoryLimitSupport(t *testing.T) {
	t.Helper()
	cmd := exec.Command("bash", "-lc", "ulimit -v 65536")
	output, err := cmd.CombinedOutput()
	if err != nil {
		t.Fatalf("this environment does not support Linux-style virtual memory limits for MLE tests: %s; run ./tests/dockertest/run_test.sh ./internal/executor for the Docker-backed executor test environment", strings.TrimSpace(string(output)))
	}
}

func compileCodeCached(code string, lang contracts.Language) CompileResult {
	return Compile(context.Background(), Source{Code: code, Language: lang, Limits: DefaultRunLimits()})
}

func runCode(workDir, inputData string, lang contracts.Language, timeLimit float64, memoryLimit int, additionalArgs []string) ExecutionResult {
	limits := Limits{TimeSeconds: timeLimit, MemoryMB: memoryLimit}
	program := CompiledProgram{Dir: workDir, Language: lang, Limits: limits}
	return Run(context.Background(), program, inputData, additionalArgs, limits)
}

func truncateText(value string, maxChars, maxLines int) string {
	lines := strings.Split(value, "\n")
	if len(lines) > maxLines {
		lines = lines[:maxLines]
		value = strings.Join(lines, "\n")
	}
	if len(value) > maxChars {
		return value[:maxChars]
	}
	return value
}

func TestSupportedLanguagesAreRegisteredForExecutionAndSmokeTests(t *testing.T) {
	smokeCasesByLanguage := map[contracts.Language]languageSmokeCase{}
	for _, smokeCase := range supportedLanguageSmokeCases() {
		if _, exists := smokeCasesByLanguage[smokeCase.Lang]; exists {
			t.Fatalf("duplicate smoke case for language %q", smokeCase.Lang)
		}
		smokeCasesByLanguage[smokeCase.Lang] = smokeCase
	}

	for language := range contracts.SupportedLanguages {
		if _, ok := languages[language]; !ok {
			t.Errorf("supported language %q is missing from executor language registry", language)
		}
		if _, ok := smokeCasesByLanguage[language]; !ok {
			t.Errorf("supported language %q is missing from supportedLanguageSmokeCases", language)
		}
	}
	for language := range languages {
		if !contracts.IsSupportedLanguage(language) {
			t.Errorf("executor language registry contains unsupported language %q", language)
		}
	}
	for language := range smokeCasesByLanguage {
		if !contracts.IsSupportedLanguage(language) {
			t.Errorf("supportedLanguageSmokeCases contains unsupported language %q", language)
		}
	}
}

func TestCompileCodeCachedFailureDoesNotCache(t *testing.T) {
	requireCommands(t, "g++")

	invalidCPP := `#include <iostream>

int main() {
    std::cout << "Hello";
`

	cacheDir := GetCacheDirectory(invalidCPP, "cpp23")
	_ = os.RemoveAll(cacheDir)

	result := compileCodeCached(invalidCPP, "cpp23")
	if result.Success {
		t.Fatalf("compileCodeCached() unexpectedly succeeded for invalid code")
	}
	if result.ReturnCode == 0 {
		t.Fatalf("compileCodeCached() returned success code for invalid code")
	}
	if result.Stderr == "" {
		t.Fatalf("compileCodeCached() stderr was empty for invalid code")
	}
	if _, err := os.Stat(cacheDir); !os.IsNotExist(err) {
		t.Fatalf("failed compilation should not leave cache directory %q behind", cacheDir)
	}
}

func TestCompileCodeCachedDefinesBOJMacros(t *testing.T) {
	requireCommands(t, "g++", "gcc")

	tests := []struct {
		name string
		lang contracts.Language
		code string
	}{
		{
			name: "cpp23",
			lang: contracts.LanguageCpp23,
			code: `#include <iostream>

int main() {
#ifdef ONLINE_JUDGE
    const char* oj = "OJ";
#else
    const char* oj = "LOCAL";
#endif
#ifdef BOJ
    const char* boj = "BOJ";
#else
    const char* boj = "NOBOJ";
#endif
    std::cout << oj << " " << boj << "\n";
    return 0;
}
`,
		},
		{
			name: "c11",
			lang: contracts.LanguageC11,
			code: `#include <stdio.h>

int main() {
#ifdef ONLINE_JUDGE
    const char* oj = "OJ";
#else
    const char* oj = "LOCAL";
#endif
#ifdef BOJ
    const char* boj = "BOJ";
#else
    const char* boj = "NOBOJ";
#endif
    printf("%s %s\n", oj, boj);
    return 0;
}
`,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			cacheDir := GetCacheDirectory(tt.code, tt.lang)
			_ = os.RemoveAll(cacheDir)

			compileResult := compileCodeCached(tt.code, tt.lang)
			if !compileResult.Success {
				t.Fatalf("compileCodeCached() failed: %+v", compileResult)
			}

			runResult := runCode(compileResult.Directory, "", tt.lang, 2, 256, nil)
			if !runResult.Success {
				t.Fatalf("runCode() failed: %+v", runResult)
			}
			if got := CleanStdout(runResult.Stdout, "no"); got != "OJ BOJ" {
				t.Fatalf("runCode() stdout = %q, want %q", got, "OJ BOJ")
			}
		})
	}
}

func TestRunCodeRuntimeErrorVerdict(t *testing.T) {
	requireCommands(t, Python313Command)

	pythonCode := `raise RuntimeError("boom")`

	compileResult := compileCodeCached(pythonCode, "python3")
	if !compileResult.Success {
		t.Fatalf("compileCodeCached() failed: %+v", compileResult)
	}

	runResult := runCode(compileResult.Directory, "", "python3", 2, 256, nil)
	if runResult.Success {
		t.Fatalf("runCode() unexpectedly succeeded: %+v", runResult)
	}
	if runResult.Verdict != contracts.VerdictRuntimeError {
		t.Fatalf("runCode() verdict = %q, want %q", runResult.Verdict, "RTE")
	}
	if runResult.ReturnCode == 0 {
		t.Fatalf("runCode() return code = 0 for runtime error")
	}
	if runResult.Stderr == "" {
		t.Fatalf("runCode() stderr was empty for runtime error")
	}
}

func TestRunCodeTimeoutVerdict(t *testing.T) {
	requireCommands(t, Python313Command)

	pythonCode := `while True:
    pass
`

	compileResult := compileCodeCached(pythonCode, "python3")
	if !compileResult.Success {
		t.Fatalf("compileCodeCached() failed: %+v", compileResult)
	}

	runResult := runCode(compileResult.Directory, "", "python3", 1, 256, nil)
	if runResult.Success {
		t.Fatalf("runCode() unexpectedly succeeded: %+v", runResult)
	}
	if runResult.Verdict != contracts.VerdictTimeLimit {
		t.Fatalf("runCode() verdict = %q, want %q", runResult.Verdict, "TLE")
	}
	if runResult.ReturnCode != -101 {
		t.Fatalf("runCode() return code = %d, want -101", runResult.ReturnCode)
	}
	if runResult.Time < 1.0 {
		t.Fatalf("runCode() time = %.3f, want >= 1.0", runResult.Time)
	}
}

func TestRunCodeOutputLimitVerdict(t *testing.T) {
	requireCommands(t, Python313Command)

	pythonCode := fmt.Sprintf(`import sys
sys.stdout.write("x" * %d)
`, MaxRunStdoutBytes+1)

	compileResult := compileCodeCached(pythonCode, "python3")
	if !compileResult.Success {
		t.Fatalf("compileCodeCached() failed: %+v", compileResult)
	}

	runResult := runCode(compileResult.Directory, "", "python3", 2, 256, nil)
	if runResult.Success {
		t.Fatalf("runCode() unexpectedly succeeded: %+v", runResult)
	}
	if runResult.Verdict != contracts.VerdictOutputLimit {
		t.Fatalf("runCode() verdict = %q, want %q", runResult.Verdict, contracts.VerdictOutputLimit)
	}
	if runResult.ReturnCode != OutputLimitReturnCode {
		t.Fatalf("runCode() return code = %d, want %d", runResult.ReturnCode, OutputLimitReturnCode)
	}
	if len(runResult.Stdout) < MaxRunStdoutBytes {
		t.Fatalf("runCode() stdout length = %d, want at least %d", len(runResult.Stdout), MaxRunStdoutBytes)
	}
	if !strings.Contains(runResult.Stdout, "output limit exceeded") {
		t.Fatalf("runCode() stdout did not include output limit message")
	}
}

func TestRunCodeMemoryLimitVerdict(t *testing.T) {
	requireCommands(t, "g++")
	requireVirtualMemoryLimitSupport(t)

	cppCode := `#include <vector>

int main() {
    std::vector<char> buf(1024ULL * 1024ULL * 1024ULL, 1);
    return buf[0];
}
`

	compileResult := compileCodeCached(cppCode, "cpp23")
	if !compileResult.Success {
		t.Fatalf("compileCodeCached() failed: %+v", compileResult)
	}

	runResult := runCode(compileResult.Directory, "", "cpp23", 5, 64, nil)
	if runResult.Success {
		t.Fatalf("runCode() unexpectedly succeeded: %+v", runResult)
	}
	if runResult.Verdict != contracts.VerdictMemoryLimit {
		t.Fatalf("runCode() verdict = %q, want %q; full result: %+v", runResult.Verdict, "MLE", runResult)
	}
}

func TestRunCodeLowNativeMemoryLimitStillStartsBinary(t *testing.T) {
	requireCommands(t, "g++")
	requireVirtualMemoryLimitSupport(t)

	cppCode := `#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b << "\n";
    return 0;
}
`

	compileResult := compileCodeCached(cppCode, "cpp23")
	if !compileResult.Success {
		t.Fatalf("compileCodeCached() failed: %+v", compileResult)
	}

	runResult := runCode(compileResult.Directory, "1 2\n", "cpp23", 2, 4, nil)
	if !runResult.Success {
		t.Fatalf("runCode() failed under low native memory limit: %+v", runResult)
	}
	if got := CleanStdout(runResult.Stdout, "no"); got != "3" {
		t.Fatalf("runCode() stdout = %q, want %q", got, "3")
	}
}

func TestRunCodeAllowsNativeStackWithinMemoryLimit(t *testing.T) {
	requireCommands(t, "g++")
	requireVirtualMemoryLimitSupport(t)

	cppCode := `#include <iostream>

int main() {
    volatile char buf[48 * 1024 * 1024];
    buf[0] = 1;
    buf[sizeof(buf) - 1] = 2;
    std::cout << int(buf[0] + buf[sizeof(buf) - 1]) << "\n";
    return 0;
}
`

	compileResult := compileCodeCached(cppCode, "cpp23")
	if !compileResult.Success {
		t.Fatalf("compileCodeCached() failed: %+v", compileResult)
	}

	runResult := runCode(compileResult.Directory, "", "cpp23", 2, 512, nil)
	if !runResult.Success {
		t.Fatalf("runCode() failed with stack allocation inside memory limit: %+v", runResult)
	}
	if got := CleanStdout(runResult.Stdout, "no"); got != "3" {
		t.Fatalf("runCode() stdout = %q, want %q", got, "3")
	}
}

func TestRunCodeSimpleAPlusBSupportedLanguages(t *testing.T) {
	for _, tc := range supportedLanguageSmokeCases() {
		t.Run(tc.Name, func(t *testing.T) {
			requireCommands(t, tc.RequiredExecutables...)
			requirePaths(t, tc.RequiredPaths...)

			compileResult := compileCodeCached(tc.Program, tc.Lang)
			if !compileResult.Success {
				t.Fatalf("compileCodeCached() failed: %+v", compileResult)
			}

			timeLimit := 2.0
			if tc.Lang == contracts.LanguageNodeJS {
				timeLimit = 5.0
			}
			runResult := runCode(compileResult.Directory, tc.Input, tc.Lang, timeLimit, 256, nil)
			if !runResult.Success {
				t.Fatalf("runCode() failed: %+v", runResult)
			}
			if runResult.Verdict != contracts.VerdictAccepted {
				t.Fatalf("runCode() verdict = %q, want %q", runResult.Verdict, "AC")
			}
			if runResult.ReturnCode != 0 {
				t.Fatalf("runCode() return code = %d, want 0", runResult.ReturnCode)
			}
			if got := CleanStdout(runResult.Stdout, "no"); got != tc.Want {
				t.Fatalf("runCode() stdout = %q, want %q", got, tc.Want)
			}
		})
	}
}

func TestCsharpTemplateUsesRuntimeNuGetRoot(t *testing.T) {
	requirePaths(t, "/var/task/CsharpApp/obj/project.assets.json")

	data, err := os.ReadFile("/var/task/CsharpApp/obj/project.assets.json")
	if err != nil {
		t.Fatalf("failed to read C# template assets: %v", err)
	}
	text := string(data)
	if !strings.Contains(text, "/tmp/dotnet/.nuget/packages/") {
		t.Fatalf("project.assets.json did not reference runtime NuGet root: %s", truncateText(text, 500, 20))
	}
	if strings.Contains(text, "/var/task/dotnet/.nuget/packages/") {
		t.Fatalf("project.assets.json still referenced read-only NuGet root: %s", truncateText(text, 500, 20))
	}
}
