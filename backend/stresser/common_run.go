package main

import (
	"bytes"
	"context"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"log"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"strings"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

var (
	cppCommonFlags = []string{"-O2", "-Wall", "-lm", "-I/opt/testlib", "-DONLINE_JUDGE", "-DBOJ"}
	cCommonFlags   = []string{"-O2", "-Wall", "-lm", "-DONLINE_JUDGE", "-DBOJ"}
)

const (
	python313Command      = "python3.13"
	maxCompileStdoutBytes = 256 << 10
	maxCompileStderrBytes = 1 << 20
	maxRunStdoutBytes     = 8 << 20
	maxRunStderrBytes     = 1 << 20
	outputLimitReturnCode = -103
)

type boundedBuffer struct {
	buffer bytes.Buffer
	limit  int
	total  int
}

func newBoundedBuffer(limit int) *boundedBuffer {
	return &boundedBuffer{limit: limit}
}

func (b *boundedBuffer) Write(p []byte) (int, error) {
	b.total += len(p)
	if b.limit <= 0 || b.buffer.Len() >= b.limit {
		return len(p), nil
	}
	remaining := b.limit - b.buffer.Len()
	if len(p) > remaining {
		_, _ = b.buffer.Write(p[:remaining])
		return len(p), nil
	}
	_, _ = b.buffer.Write(p)
	return len(p), nil
}

func (b *boundedBuffer) String() string {
	return b.buffer.String()
}

func (b *boundedBuffer) Exceeded() bool {
	return b.total > b.limit
}

func appendOutputLimitMessage(text, streamName string, limitBytes int) string {
	message := fmt.Sprintf("\n[output limit exceeded: %s exceeded %d bytes]", streamName, limitBytes)
	if text == "" {
		return strings.TrimPrefix(message, "\n")
	}
	return text + message
}

type languageSpec struct {
	SourceExt   string
	CompileCmds [][]string
	RunCmd      []string
	// BuildRunCmd is used when the argv depends on runtime limits, such as JVM heap sizing.
	BuildRunCmd func(memoryLimit int) []string
	// BuildRunEnv is used when the runtime needs limit-aware environment variables.
	BuildRunEnv func(memoryLimit int) []string
	// RunDirectly bypasses the shell/ulimit runner and execs the program directly.
	RunDirectly bool
}

var languages = map[contracts.Language]languageSpec{
	contracts.LanguageCpp23: {
		SourceExt: "cpp",
		CompileCmds: [][]string{
			append([]string{"g++", "-std=gnu++23", "Main.cpp", "-o", "a.out"}, cppCommonFlags...),
		},
		RunCmd: []string{"./a.out"},
	},
	contracts.LanguageCpp20: {
		SourceExt: "cpp",
		CompileCmds: [][]string{
			append([]string{"g++", "-std=gnu++20", "Main.cpp", "-o", "a.out"}, cppCommonFlags...),
		},
		RunCmd: []string{"./a.out"},
	},
	contracts.LanguageCpp17: {
		SourceExt: "cpp",
		CompileCmds: [][]string{
			append([]string{"g++", "-std=gnu++17", "Main.cpp", "-o", "a.out"}, cppCommonFlags...),
		},
		RunCmd: []string{"./a.out"},
	},
	contracts.LanguageCpp14: {
		SourceExt: "cpp",
		CompileCmds: [][]string{
			append([]string{"g++", "-std=gnu++14", "Main.cpp", "-o", "a.out"}, cppCommonFlags...),
		},
		RunCmd: []string{"./a.out"},
	},
	contracts.LanguageC11: {
		SourceExt: "c",
		CompileCmds: [][]string{
			append([]string{"gcc", "Main.c", "-o", "Main", "-std=gnu11"}, cCommonFlags...),
		},
		RunCmd: []string{"./Main"},
	},
	contracts.LanguageC99: {
		SourceExt: "c",
		CompileCmds: [][]string{
			append([]string{"gcc", "Main.c", "-o", "Main", "-std=gnu99"}, cCommonFlags...),
		},
		RunCmd: []string{"./Main"},
	},
	contracts.LanguagePython3: {
		SourceExt: "py",
		CompileCmds: [][]string{
			{python313Command, "-W", "ignore", "-c", "import py_compile; py_compile.compile(r'Main.py')"},
		},
		RunCmd: []string{python313Command, "-W", "ignore", "Main.py"},
	},
	contracts.LanguageJava: {
		SourceExt: "java",
		CompileCmds: [][]string{
			{"javac", "--release", "11", "-encoding", "UTF-8", "Main.java"},
		},
		BuildRunCmd: func(memoryLimit int) []string {
			return []string{
				"java",
				fmt.Sprintf("-Xmx%dm", memoryLimit),
				"-Dfile.encoding=UTF-8",
				"Main",
			}
		},
		RunDirectly: true,
	},
	contracts.LanguageNodeJS: {
		SourceExt:   "js",
		CompileCmds: nil,
		RunCmd:      []string{"node", "--stack-size=65536", "Main.js"},
		RunDirectly: true,
	},
	contracts.LanguagePyPy3: {
		SourceExt: "py",
		CompileCmds: [][]string{
			{"pypy3", "-W", "ignore", "-c", "import py_compile; py_compile.compile(r'Main.py')"},
		},
		RunCmd: []string{"pypy3", "-W", "ignore", "Main.py"},
	},
	contracts.LanguageGolang: {
		SourceExt: "go",
		CompileCmds: [][]string{
			{"go", "build", "-o", "Main", "Main.go"},
		},
		RunCmd:      []string{"./Main"},
		RunDirectly: true,
		BuildRunEnv: func(memoryLimit int) []string {
			return []string{fmt.Sprintf("GOMEMLIMIT=%dMiB", atLeast(memoryLimit, 32))}
		},
	},
	contracts.LanguageKotlin: {
		SourceExt: "kt",
		CompileCmds: [][]string{
			{"kotlinc-jvm", "-J-Xms1024M", "-J-Xmx1600M", "-J-Xss512M", "-include-runtime", "-d", "Main.jar", "Main.kt"},
		},
		RunCmd: []string{
			"java",
			"-Xms1024M",
			"-Xmx1600M",
			"-Xss512M",
			"-Dfile.encoding=UTF-8",
			"-XX:+UseSerialGC",
			"-DONLINE_JUDGE=1",
			"-DBOJ=1",
			"-jar",
			"Main.jar",
		},
		RunDirectly: true,
	},
	contracts.LanguageRust2021: {
		SourceExt: "rs",
		CompileCmds: [][]string{
			{"rustc", "--edition", "2021", "-O", "-o", "Main", "Main.rs"},
		},
		RunCmd: []string{"./Main"},
	},
	contracts.LanguageCSharp: {
		SourceExt: "cs",
		CompileCmds: [][]string{
			{"rm", "-rf", "./CsharpApp"},
			{"cp", "-r", "/var/task/CsharpApp", "./CsharpApp"},
			{"mv", "./Main.cs", "./CsharpApp/Program.cs"},
			{"dotnet", "publish", "CsharpApp", "--configuration", "Release", "--self-contained", "true", "--runtime", dotnetRuntimeIdentifier(), "--no-restore"},
		},
		RunCmd:      []string{dotnetPublishedBinaryPath()},
		RunDirectly: true,
	},
}

type compileResult struct {
	Success    bool
	Directory  string
	Stderr     string
	Stdout     string
	ReturnCode int
	Command    []string
	StepIndex  int
}

type executionResult struct {
	Success    bool
	Verdict    contracts.Verdict
	ReturnCode int
	Stdout     string
	Stderr     string
	Time       float64
}

func getCodeHash(code string, lang contracts.Language) string {
	sum := sha256.Sum256([]byte(fmt.Sprintf("%q:%q", code, lang)))
	return hex.EncodeToString(sum[:])
}

func getCacheDirectory(code string, lang contracts.Language) string {
	return filepath.Join("/tmp/compile", getCodeHash(code, lang))
}

func compileCodeCached(code string, lang contracts.Language) compileResult {
	spec, ok := languages[lang]
	if !ok {
		return compileResult{Success: false, Stderr: fmt.Sprintf("Invalid language: %s", lang)}
	}
	directory := getCacheDirectory(code, lang)
	if _, err := os.Stat(directory); err == nil {
		log.Printf("Using cached compilation for %s", directory)
		return compileResult{Success: true, Directory: directory}
	}
	log.Printf("Compiling for the first time in %s", directory)
	return compileCode(directory, code, spec)
}

func compileCode(workDir, code string, spec languageSpec) compileResult {
	if err := os.MkdirAll(workDir, 0o755); err != nil {
		return compileResult{Success: false, Stderr: err.Error()}
	}
	sourcePath := filepath.Join(workDir, fmt.Sprintf("Main.%s", spec.SourceExt))
	if err := os.WriteFile(sourcePath, []byte(code), 0o644); err != nil {
		return compileResult{Success: false, Stderr: err.Error()}
	}
	for i, cmdArgs := range spec.CompileCmds {
		cmd := exec.Command(cmdArgs[0], cmdArgs[1:]...)
		cmd.Dir = workDir
		cmd.Env = cleanChildEnv(nil)
		stdout := newBoundedBuffer(maxCompileStdoutBytes)
		stderr := newBoundedBuffer(maxCompileStderrBytes)
		cmd.Stdout = stdout
		cmd.Stderr = stderr
		err := cmd.Run()
		stdoutText := shortenPathsToFilenames(stdout.String())
		stderrText := shortenPathsToFilenames(stderr.String())
		if stdout.Exceeded() || stderr.Exceeded() {
			exitCode := 0
			if err != nil {
				exitCode = -1
				if exitErr, ok := err.(*exec.ExitError); ok {
					exitCode = exitErr.ExitCode()
				}
			}
			if stdout.Exceeded() {
				stdoutText = appendOutputLimitMessage(stdoutText, "compiler stdout", maxCompileStdoutBytes)
			}
			if stderr.Exceeded() {
				stderrText = appendOutputLimitMessage(stderrText, "compiler stderr", maxCompileStderrBytes)
			}
			log.Printf(
				"Compile step %d exceeded output limit: cmd=%q exit=%d stdout_exceeded=%t stderr_exceeded=%t",
				i,
				strings.Join(cmdArgs, " "),
				exitCode,
				stdout.Exceeded(),
				stderr.Exceeded(),
			)
			_ = os.RemoveAll(workDir)
			return compileResult{
				Success:    false,
				Stdout:     stdoutText,
				Stderr:     stderrText,
				ReturnCode: exitCode,
				Command:    append([]string{}, cmdArgs...),
				StepIndex:  i,
			}
		}
		if err != nil {
			exitCode := -1
			if exitErr, ok := err.(*exec.ExitError); ok {
				exitCode = exitErr.ExitCode()
			}
			log.Printf(
				"Compile step %d failed: cmd=%q exit=%d stdout=%q stderr=%q",
				i,
				strings.Join(cmdArgs, " "),
				exitCode,
				truncateTestcase(stdoutText, 1200, 20),
				truncateTestcase(stderrText, 1200, 20),
			)
			_ = os.RemoveAll(workDir)
			return compileResult{
				Success:    false,
				Stdout:     stdoutText,
				Stderr:     stderrText,
				ReturnCode: exitCode,
				Command:    append([]string{}, cmdArgs...),
				StepIndex:  i,
			}
		}
	}
	log.Printf("Compiled %s", sourcePath)
	return compileResult{Success: true, Directory: workDir}
}

func (spec languageSpec) resolvedRunCmd(memoryLimit int) []string {
	if spec.BuildRunCmd != nil {
		return append([]string{}, spec.BuildRunCmd(memoryLimit)...)
	}
	return append([]string{}, spec.RunCmd...)
}

func (spec languageSpec) resolvedRunEnv(memoryLimit int) []string {
	if spec.BuildRunEnv != nil {
		return append([]string{}, spec.BuildRunEnv(memoryLimit)...)
	}
	return nil
}

func compileAndGetDir(code string, lang contracts.Language, errorType contracts.ErrorType) (string, error) {
	result := compileCodeCached(code, lang)
	if !result.Success {
		details := map[string]any{
			"stderr":     result.Stderr,
			"stdout":     result.Stdout,
			"returnCode": result.ReturnCode,
			"step":       result.StepIndex,
		}
		if len(result.Command) > 0 {
			details["command"] = strings.Join(result.Command, " ")
		}
		log.Printf(
			"Compile failed: step=%d exit=%d cmd=%q stderr=%q stdout=%q",
			result.StepIndex,
			result.ReturnCode,
			details["command"],
			truncateTestcase(result.Stderr, 1200, 20),
			truncateTestcase(result.Stdout, 1200, 20),
		)
		return "", NewResponseError(errorType, details)
	}
	return result.Directory, nil
}

func isMemoryLimitExceeded(language contracts.Language, stderr string) bool {
	switch language {
	case contracts.LanguageCpp23, contracts.LanguageCpp20, contracts.LanguageCpp17, contracts.LanguageCpp14, contracts.LanguageC11, contracts.LanguageC99:
		return strings.Contains(stderr, "std::bad_alloc")
	case contracts.LanguagePython3, contracts.LanguagePyPy3:
		return strings.Contains(stderr, "MemoryError")
	case contracts.LanguageJava, contracts.LanguageKotlin:
		return strings.Contains(stderr, "OutOfMemoryError")
	case contracts.LanguageNodeJS:
		return strings.Contains(stderr, "heap out of memory")
	case contracts.LanguageGolang:
		return strings.Contains(strings.ToLower(stderr), "out of memory")
	default:
		return false
	}
}

func runCode(workDir, inputData string, lang contracts.Language, timeLimit float64, memoryLimit int, additionalArgs []string) executionResult {
	spec, ok := languages[lang]
	if !ok {
		return executionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -100}
	}
	if _, err := os.Stat(workDir); err != nil {
		log.Printf("Work directory does not exist: %s", workDir)
		return executionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -100}
	}
	if additionalArgs == nil {
		additionalArgs = []string{}
	}

	inputFilePath := ""
	var stdinFile *os.File
	if inputData != "" {
		inputFilePath = filepath.Join(workDir, "input.txt")
		if err := os.WriteFile(inputFilePath, []byte(inputData), 0o644); err != nil {
			return executionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: shortenPathsToFilenames(err.Error())}
		}
		var err error
		stdinFile, err = os.Open(inputFilePath)
		if err != nil {
			_ = os.Remove(inputFilePath)
			return executionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: shortenPathsToFilenames(err.Error())}
		}
	}
	defer func() {
		if stdinFile != nil {
			_ = stdinFile.Close()
		}
		if inputFilePath != "" {
			_ = os.Remove(inputFilePath)
		}
	}()

	timeout := time.Duration(timeLimit * float64(time.Second))
	if timeout <= 0 {
		timeout = 2 * time.Second
	}
	start := time.Now()
	ctx, cancel := context.WithTimeout(context.Background(), timeout)
	defer cancel()

	memoryKB := memoryLimit * 1024
	command := spec.resolvedRunCmd(memoryLimit)
	command = append(command, additionalArgs...)
	if len(command) == 0 {
		return executionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -100}
	}
	var (
		cmd *exec.Cmd
	)
	if spec.RunDirectly {
		cmd = exec.CommandContext(ctx, command[0], command[1:]...)
		if stdinFile != nil {
			cmd.Stdin = stdinFile
		}
	} else {
		stdinPath := "/dev/null"
		if inputFilePath != "" {
			stdinPath = inputFilePath
		}
		script := `mem="$1"; stdin_path="$2"; shift 2; ulimit -c 0; ulimit -v "$mem"; ulimit -u 0; exec "$@" < "$stdin_path"`
		args := []string{"-lc", script, "bash", fmt.Sprintf("%d", memoryKB), stdinPath}
		args = append(args, command...)
		cmd = exec.CommandContext(ctx, "bash", args...)
	}
	cmd.Dir = workDir
	cmd.Env = cleanChildEnv(spec.resolvedRunEnv(memoryLimit))
	stdout := newBoundedBuffer(maxRunStdoutBytes)
	stderr := newBoundedBuffer(maxRunStderrBytes)
	cmd.Stdout = stdout
	cmd.Stderr = stderr
	err := cmd.Run()
	timeSpent := roundSeconds(time.Since(start))

	stdoutText := stdout.String()
	stderrText := shortenPathsToFilenames(stderr.String())

	if stdout.Exceeded() || stderr.Exceeded() {
		if stdout.Exceeded() {
			stdoutText = appendOutputLimitMessage(stdoutText, "stdout", maxRunStdoutBytes)
		}
		if stderr.Exceeded() {
			stderrText = appendOutputLimitMessage(stderrText, "stderr", maxRunStderrBytes)
		}
		return executionResult{
			Success:    false,
			Verdict:    contracts.VerdictOutputLimit,
			ReturnCode: outputLimitReturnCode,
			Stdout:     stdoutText,
			Stderr:     stderrText,
			Time:       timeSpent,
		}
	}

	if ctx.Err() == context.DeadlineExceeded {
		return executionResult{Success: false, Verdict: contracts.VerdictTimeLimit, ReturnCode: -101, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
	}

	if err != nil {
		exitCode := -102
		if exitErr, ok := err.(*exec.ExitError); ok {
			exitCode = exitErr.ExitCode()
		}
		if exitCode == 137 || exitCode == -9 {
			verdict := contracts.VerdictMemoryLimit
			if timeSpent >= timeLimit*0.99 {
				verdict = contracts.VerdictTimeLimit
			}
			return executionResult{Success: false, Verdict: verdict, ReturnCode: exitCode, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
		}
		if isMemoryLimitExceeded(lang, stderrText) {
			return executionResult{Success: false, Verdict: contracts.VerdictMemoryLimit, ReturnCode: exitCode, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
		}
		return executionResult{Success: false, Verdict: contracts.VerdictRuntimeError, ReturnCode: exitCode, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
	}

	return executionResult{Success: true, Verdict: contracts.VerdictAccepted, ReturnCode: 0, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
}

func atLeast(value, minimum int) int {
	if value < minimum {
		return minimum
	}
	return value
}

func cleanChildEnv(extra []string) []string {
	env := []string{
		"PATH=/usr/local/go/bin:/opt/kotlinc/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
		"HOME=/tmp",
		"TMPDIR=/tmp",
		"LANG=C.UTF-8",
		"LC_ALL=C.UTF-8",
		"GOCACHE=/tmp/.cache/go-build",
		"DOTNET_ROOT=/usr/share/dotnet",
		"DOTNET_CLI_HOME=/tmp/dotnet",
		"DOTNET_NUGET_SIGNATURE_VERIFICATION=false",
		"DOTNET_SKIP_FIRST_TIME_EXPERIENCE=1",
		"DOTNET_NOLOGO=1",
		"NUGET_PACKAGES=/tmp/dotnet/.nuget/packages",
	}
	env = append(env, extra...)
	return env
}

func dotnetRuntimeIdentifier() string {
	switch runtime.GOARCH {
	case "amd64":
		return "linux-x64"
	case "arm64":
		return "linux-arm64"
	default:
		return "linux-" + runtime.GOARCH
	}
}

func dotnetPublishedBinaryPath() string {
	return filepath.Join(".", "CsharpApp", "bin", "Release", "net8.0", dotnetRuntimeIdentifier(), "publish", "CsharpApp")
}

const (
	testFile              = "input.txt"
	participantOutputFile = "participant.txt"
	juryOutputFile        = "jury.txt"
	resultFile            = "result.txt"
)

func runChecker(workDir, testdata, participantOutput, juryOutput string, timeLimit float64, memoryLimit int) executionResult {
	testFilePath := filepath.Join(workDir, testFile)
	participantPath := filepath.Join(workDir, participantOutputFile)
	juryPath := filepath.Join(workDir, juryOutputFile)
	resultPath := filepath.Join(workDir, resultFile)
	defer func() {
		for _, path := range []string{testFilePath, participantPath, juryPath, resultPath} {
			_ = os.Remove(path)
		}
	}()

	if err := os.WriteFile(testFilePath, []byte(testdata), 0o644); err != nil {
		return executionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: err.Error()}
	}
	if err := os.WriteFile(participantPath, []byte(participantOutput), 0o644); err != nil {
		return executionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: err.Error()}
	}
	if err := os.WriteFile(juryPath, []byte(juryOutput), 0o644); err != nil {
		return executionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: err.Error()}
	}

	checkerExecution := runCode(workDir, "", contracts.LanguageCpp23, timeLimit, memoryLimit, []string{testFile, participantOutputFile, juryOutputFile, resultFile})
	if data, err := os.ReadFile(resultPath); err == nil {
		checkerExecution.Stdout = string(data)
	}
	if checkerExecution.ReturnCode == 1 || checkerExecution.ReturnCode == 2 {
		checkerExecution.Success = true
		checkerExecution.Verdict = contracts.VerdictWrongAnswer
	}
	return checkerExecution
}

func generateByCaseProvider(caseProvider contracts.CaseProvider, randomSeed int) (string, contracts.GeneratedBy, *executionResult, error) {
	switch caseProvider.Type {
	case contracts.CaseProviderText:
		return cleanStdout(caseProvider.Content, "always"), contracts.GeneratedBy{
			Stage: caseProvider.Type,
			ID:    caseProvider.ID,
		}, nil, nil
	case contracts.CaseProviderGenerator, contracts.CaseProviderSinglegen:
		args := []string{}
		generatedBy := contracts.GeneratedBy{Stage: caseProvider.Type, ID: caseProvider.ID}
		if caseProvider.Type == contracts.CaseProviderGenerator {
			seed := fmt.Sprintf("%d", randomSeed)
			args = []string{seed}
			generatedBy.Seed = stringPtr(seed)
		}
		execution := runCode(
			caseProvider.Code,
			"",
			caseProvider.Language,
			2,
			1024,
			args,
		)
		if !execution.Success {
			return "", contracts.GeneratedBy{}, &execution, nil
		}
		return cleanStdout(execution.Stdout, "always"), generatedBy, nil, nil
	default:
		return "", contracts.GeneratedBy{}, nil, NewResponseError(
			contracts.ErrorTypeInternalServerError,
			map[string]any{"message": fmt.Sprintf("Unknown case provider type: %s", caseProvider.Type)},
		)
	}
}

func stressTestIteration(targetCode, correctCode compiledProgram, checkerCode *compiledProgram, caseProvider compiledCaseProvider, randomSeed int) (stressIteration, error) {
	testcase, generatedBy, generateError, err := caseProvider.Generate(randomSeed)
	if err != nil {
		return stressIteration{}, err
	}
	if generateError != nil {
		return stressIteration{}, NewResponseError(contracts.ErrorTypeGeneratorExecutionFailed, map[string]any{
			"verdict":    generateError.Verdict,
			"returncode": generateError.ReturnCode,
			"stdout":     generateError.Stdout,
			"stderr":     generateError.Stderr,
			"time":       generateError.Time,
			"input":      "",
		})
	}

	correctExecution := runCode(correctCode.Dir, testcase, correctCode.Language, correctCode.TimeLimit, correctCode.MemoryLimit, nil)
	if !correctExecution.Success {
		return stressIteration{}, NewResponseError(contracts.ErrorTypeCorrectExecutionFailed, map[string]any{
			"verdict":    correctExecution.Verdict,
			"returncode": correctExecution.ReturnCode,
			"stdout":     correctExecution.Stdout,
			"stderr":     correctExecution.Stderr,
			"time":       correctExecution.Time,
			"input":      testcase,
		})
	}

	targetExecution := runCode(targetCode.Dir, testcase, targetCode.Language, targetCode.TimeLimit, targetCode.MemoryLimit, nil)
	var runSummary targetRun
	if !targetExecution.Success {
		runSummary = targetRun{
			Verdict:       targetExecution.Verdict,
			TargetOutput:  targetExecution.Stdout,
			CheckerOutput: "",
			Stderr:        targetExecution.Stderr,
			Time:          targetExecution.Time,
		}
	} else if checkerCode != nil {
		cleanCorrect := cleanStdout(correctExecution.Stdout, "no")
		cleanTarget := cleanStdout(targetExecution.Stdout, "no")
		checkerExecution := runChecker(checkerCode.Dir, testcase, cleanTarget, cleanCorrect, checkerCode.TimeLimit, checkerCode.MemoryLimit)
		if checkerExecution.Success {
			runSummary = targetRun{
				Verdict:       checkerExecution.Verdict,
				TargetOutput:  targetExecution.Stdout,
				CheckerOutput: checkerExecution.Stdout,
				Stderr:        checkerExecution.Stderr,
				Time:          checkerExecution.Time,
			}
		} else {
			stderr := fmt.Sprintf("stderr: %s\nfile output:\n%s\ntestcase:\n%s", checkerExecution.Stderr, checkerExecution.Stdout, testcase)
			return stressIteration{}, NewResponseError(contracts.ErrorTypeCheckerExecutionFailed, map[string]any{
				"verdict":    checkerExecution.Verdict,
				"returncode": checkerExecution.ReturnCode,
				"stdout":     checkerExecution.Stdout,
				"stderr":     truncateTestcase(stderr, 1000, 40),
				"time":       checkerExecution.Time,
				"input":      testcase,
			})
		}
	} else {
		verdict := contracts.VerdictWrongAnswer
		if compareOutput(targetExecution.Stdout, correctExecution.Stdout) {
			verdict = contracts.VerdictAccepted
		}
		runSummary = targetRun{
			Verdict:       verdict,
			TargetOutput:  targetExecution.Stdout,
			CheckerOutput: "",
			Time:          targetExecution.Time,
		}
	}

	return stressIteration{
		Testcase:      testcase,
		GeneratedBy:   generatedBy,
		CorrectOutput: correctExecution.Stdout,
		TargetRun:     runSummary,
	}, nil
}

func roundSeconds(d time.Duration) float64 {
	return float64(d.Milliseconds()) / 1000.0
}
