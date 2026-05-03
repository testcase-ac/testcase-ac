package executor

import (
	"bytes"
	"context"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"log/slog"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"runtime"
	"strings"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

const (
	Python313Command      = "python3.13"
	MaxCompileStdoutBytes = 256 << 10
	MaxCompileStderrBytes = 1 << 20
	MaxRunStdoutBytes     = 8 << 20
	MaxRunStderrBytes     = 1 << 20
	OutputLimitReturnCode = -103
	// Very low BOJ memory limits are below the virtual memory needed to start
	// dynamically linked native binaries in the runtime image.
	// There seems to be no good way of enforcing low memory limit in docker + lamdba
	// (ex. 4MB for https://www.acmicpc.net/problem/2293)
	minNativeVirtualMemoryMB = 64
)

var (
	cppCommonFlags = []string{"-O2", "-Wall", "-lm", "-I/opt/testlib", "-DONLINE_JUDGE", "-DBOJ"}
	cCommonFlags   = []string{"-O2", "-Wall", "-lm", "-DONLINE_JUDGE", "-DBOJ"}
)

type Source struct {
	Label    string
	Code     string
	Language contracts.Language
	Limits   Limits
}

type Limits struct {
	TimeSeconds float64
	MemoryMB    int
	StdoutBytes int
	StderrBytes int
}

type CompiledProgram struct {
	Dir      string
	Label    string
	Language contracts.Language
	Limits   Limits
}

type CompileResult struct {
	Success    bool
	Program    *CompiledProgram
	Directory  string
	Stderr     string
	Stdout     string
	ReturnCode int
	Command    []string
	StepIndex  int
}

type ExecutionResult struct {
	Success    bool
	Verdict    contracts.Verdict
	ReturnCode int
	Stdout     string
	Stderr     string
	Time       float64
}

type languageSpec struct {
	SourceExt   string
	CompileCmds [][]string
	RunCmd      []string
	BuildRunCmd func(memoryLimit int) []string
	BuildRunEnv func(memoryLimit int) []string
	RunDirectly bool
}

var languages = map[contracts.Language]languageSpec{
	contracts.LanguageCpp23: {
		SourceExt:   "cpp",
		CompileCmds: [][]string{append([]string{"g++", "-std=gnu++23", "Main.cpp", "-o", "a.out"}, cppCommonFlags...)},
		RunCmd:      []string{"./a.out"},
	},
	contracts.LanguageCpp20: {
		SourceExt:   "cpp",
		CompileCmds: [][]string{append([]string{"g++", "-std=gnu++20", "Main.cpp", "-o", "a.out"}, cppCommonFlags...)},
		RunCmd:      []string{"./a.out"},
	},
	contracts.LanguageCpp17: {
		SourceExt:   "cpp",
		CompileCmds: [][]string{append([]string{"g++", "-std=gnu++17", "Main.cpp", "-o", "a.out"}, cppCommonFlags...)},
		RunCmd:      []string{"./a.out"},
	},
	contracts.LanguageCpp14: {
		SourceExt:   "cpp",
		CompileCmds: [][]string{append([]string{"g++", "-std=gnu++14", "Main.cpp", "-o", "a.out"}, cppCommonFlags...)},
		RunCmd:      []string{"./a.out"},
	},
	contracts.LanguageC11: {
		SourceExt:   "c",
		CompileCmds: [][]string{append([]string{"gcc", "Main.c", "-o", "Main", "-std=gnu11"}, cCommonFlags...)},
		RunCmd:      []string{"./Main"},
	},
	contracts.LanguageC99: {
		SourceExt:   "c",
		CompileCmds: [][]string{append([]string{"gcc", "Main.c", "-o", "Main", "-std=gnu99"}, cCommonFlags...)},
		RunCmd:      []string{"./Main"},
	},
	contracts.LanguagePython3: {
		SourceExt:   "py",
		CompileCmds: [][]string{{Python313Command, "-W", "ignore", "-c", "import py_compile; py_compile.compile(r'Main.py')"}},
		RunCmd:      []string{Python313Command, "-W", "ignore", "Main.py"},
	},
	contracts.LanguageJava: {
		SourceExt:   "java",
		CompileCmds: [][]string{{"javac", "--release", "11", "-encoding", "UTF-8", "Main.java"}},
		BuildRunCmd: func(memoryLimit int) []string {
			return []string{"java", fmt.Sprintf("-Xmx%dm", memoryLimit), "-Dfile.encoding=UTF-8", "Main"}
		},
		RunDirectly: true,
	},
	contracts.LanguageNodeJS: {
		SourceExt:   "js",
		RunCmd:      []string{"node", "--stack-size=65536", "Main.js"},
		RunDirectly: true,
	},
	contracts.LanguagePyPy3: {
		SourceExt:   "py",
		CompileCmds: [][]string{{"pypy3", "-W", "ignore", "-c", "import py_compile; py_compile.compile(r'Main.py')"}},
		RunCmd:      []string{"pypy3", "-W", "ignore", "Main.py"},
	},
	contracts.LanguageGolang: {
		SourceExt:   "go",
		CompileCmds: [][]string{{"go", "build", "-o", "Main", "Main.go"}},
		RunCmd:      []string{"./Main"},
		RunDirectly: true,
		BuildRunEnv: func(memoryLimit int) []string {
			return []string{fmt.Sprintf("GOMEMLIMIT=%dMiB", atLeast(memoryLimit, 32))}
		},
	},
	contracts.LanguageKotlin: {
		SourceExt:   "kt",
		CompileCmds: [][]string{{"kotlinc-jvm", "-J-Xms1024M", "-J-Xmx1600M", "-J-Xss512M", "-include-runtime", "-d", "Main.jar", "Main.kt"}},
		RunCmd: []string{
			"java", "-Xms1024M", "-Xmx1600M", "-Xss512M", "-Dfile.encoding=UTF-8",
			"-XX:+UseSerialGC", "-DONLINE_JUDGE=1", "-DBOJ=1", "-jar", "Main.jar",
		},
		RunDirectly: true,
	},
	contracts.LanguageRust2021: {
		SourceExt:   "rs",
		CompileCmds: [][]string{{"rustc", "--edition", "2021", "-O", "-o", "Main", "Main.rs"}},
		RunCmd:      []string{"./Main"},
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

func SupportedLanguages() map[contracts.Language]struct{} {
	out := make(map[contracts.Language]struct{}, len(languages))
	for language := range languages {
		out[language] = struct{}{}
	}
	return out
}

func DefaultRunLimits() Limits {
	return Limits{TimeSeconds: 2, MemoryMB: 1024, StdoutBytes: MaxRunStdoutBytes, StderrBytes: MaxRunStderrBytes}
}

func Compile(ctx context.Context, source Source) CompileResult {
	spec, ok := languages[source.Language]
	if !ok {
		return CompileResult{Success: false, Stderr: fmt.Sprintf("Invalid language: %s", source.Language)}
	}
	directory := GetCacheDirectory(source.Code, source.Language)
	if _, err := os.Stat(directory); err == nil {
		slog.Info("compile_cache_hit", "directory", directory, "language", source.Language)
		return compileSuccess(source, directory)
	}
	slog.Info("compile_cache_miss", "directory", directory, "language", source.Language)
	return compileCode(ctx, source, directory, spec)
}

func GetCacheDirectory(code string, lang contracts.Language) string {
	sum := sha256.Sum256([]byte(fmt.Sprintf("%q:%q", code, lang)))
	return filepath.Join("/tmp/compile", hex.EncodeToString(sum[:]))
}

func compileCode(ctx context.Context, source Source, workDir string, spec languageSpec) CompileResult {
	if err := os.MkdirAll(workDir, 0o755); err != nil {
		return CompileResult{Success: false, Stderr: err.Error()}
	}
	sourcePath := filepath.Join(workDir, fmt.Sprintf("Main.%s", spec.SourceExt))
	if err := os.WriteFile(sourcePath, []byte(source.Code), 0o644); err != nil {
		return CompileResult{Success: false, Stderr: err.Error()}
	}
	for i, cmdArgs := range spec.CompileCmds {
		cmd := exec.CommandContext(ctx, cmdArgs[0], cmdArgs[1:]...)
		cmd.Dir = workDir
		cmd.Env = cleanChildEnv(nil)
		stdout := newBoundedBuffer(MaxCompileStdoutBytes)
		stderr := newBoundedBuffer(MaxCompileStderrBytes)
		cmd.Stdout = stdout
		cmd.Stderr = stderr
		err := cmd.Run()
		stdoutText := ShortenPathsToFilenames(stdout.String())
		stderrText := ShortenPathsToFilenames(stderr.String())
		if stdout.Exceeded() || stderr.Exceeded() {
			exitCode := exitCodeOf(err)
			if stdout.Exceeded() {
				stdoutText = appendOutputLimitMessage(stdoutText, "compiler stdout", MaxCompileStdoutBytes)
			}
			if stderr.Exceeded() {
				stderrText = appendOutputLimitMessage(stderrText, "compiler stderr", MaxCompileStderrBytes)
			}
			_ = os.RemoveAll(workDir)
			return CompileResult{Success: false, Stdout: stdoutText, Stderr: stderrText, ReturnCode: exitCode, Command: append([]string{}, cmdArgs...), StepIndex: i}
		}
		if err != nil {
			exitCode := exitCodeOf(err)
			slog.Warn("compile_step_failed", "step", i, "command", strings.Join(cmdArgs, " "), "exit_code", exitCode, "stderr", stderrText, "stdout", stdoutText)
			_ = os.RemoveAll(workDir)
			return CompileResult{Success: false, Stdout: stdoutText, Stderr: stderrText, ReturnCode: exitCode, Command: append([]string{}, cmdArgs...), StepIndex: i}
		}
	}
	slog.Info("compile_done", "source_path", sourcePath)
	return compileSuccess(source, workDir)
}

func compileSuccess(source Source, directory string) CompileResult {
	program := &CompiledProgram{Dir: directory, Label: source.Label, Language: source.Language, Limits: source.Limits}
	return CompileResult{Success: true, Program: program, Directory: directory}
}

func Run(ctx context.Context, program CompiledProgram, inputData string, args []string, limits Limits) ExecutionResult {
	spec, ok := languages[program.Language]
	if !ok {
		return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -100}
	}
	if _, err := os.Stat(program.Dir); err != nil {
		slog.Error("work_directory_missing", "work_dir", program.Dir, "err", err)
		return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -100}
	}
	limits = normalizeLimits(limits, program.Limits)

	inputFilePath := ""
	var stdinFile *os.File
	if inputData != "" {
		var err error
		stdinFile, err = os.CreateTemp(program.Dir, "input-*.txt")
		if err != nil {
			return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: ShortenPathsToFilenames(err.Error())}
		}
		inputFilePath = stdinFile.Name()
		if _, err := stdinFile.WriteString(inputData); err != nil {
			_ = stdinFile.Close()
			_ = os.Remove(inputFilePath)
			return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: ShortenPathsToFilenames(err.Error())}
		}
		if _, err := stdinFile.Seek(0, 0); err != nil {
			_ = stdinFile.Close()
			_ = os.Remove(inputFilePath)
			return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: ShortenPathsToFilenames(err.Error())}
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

	timeout := time.Duration(limits.TimeSeconds * float64(time.Second))
	start := time.Now()
	runCtx, cancel := context.WithTimeout(ctx, timeout)
	defer cancel()

	command := append(spec.resolvedRunCmd(limits.MemoryMB), args...)
	if len(command) == 0 {
		return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -100}
	}
	var cmd *exec.Cmd
	if spec.RunDirectly {
		cmd = exec.CommandContext(runCtx, command[0], command[1:]...)
		if stdinFile != nil {
			cmd.Stdin = stdinFile
		}
	} else {
		stdinPath := "/dev/null"
		if inputFilePath != "" {
			stdinPath = inputFilePath
		}
		virtualMemoryMB := virtualMemoryLimitMB(program.Language, limits.MemoryMB)
		script := `mem="$1"; stdin_path="$2"; shift 2; ulimit -c 0; ulimit -v "$mem"; ulimit -s "$mem"; ulimit -u 0; exec "$@" < "$stdin_path"`
		shellArgs := []string{"-lc", script, "bash", fmt.Sprintf("%d", virtualMemoryMB*1024), stdinPath}
		shellArgs = append(shellArgs, command...)
		cmd = exec.CommandContext(runCtx, "bash", shellArgs...)
	}
	cmd.Dir = program.Dir
	cmd.Env = cleanChildEnv(spec.resolvedRunEnv(limits.MemoryMB))
	stdout := newBoundedBuffer(limits.StdoutBytes)
	stderr := newBoundedBuffer(limits.StderrBytes)
	cmd.Stdout = stdout
	cmd.Stderr = stderr
	err := cmd.Run()
	timeSpent := RoundSeconds(time.Since(start))

	stdoutText := stdout.String()
	stderrText := ShortenPathsToFilenames(stderr.String())
	if stdout.Exceeded() || stderr.Exceeded() {
		if stdout.Exceeded() {
			stdoutText = appendOutputLimitMessage(stdoutText, "stdout", limits.StdoutBytes)
		}
		if stderr.Exceeded() {
			stderrText = appendOutputLimitMessage(stderrText, "stderr", limits.StderrBytes)
		}
		return ExecutionResult{Success: false, Verdict: contracts.VerdictOutputLimit, ReturnCode: OutputLimitReturnCode, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
	}
	if runCtx.Err() == context.DeadlineExceeded {
		return ExecutionResult{Success: false, Verdict: contracts.VerdictTimeLimit, ReturnCode: -101, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
	}
	if err != nil {
		exitCode := exitCodeOf(err)
		if exitCode == 137 || exitCode == -9 {
			verdict := contracts.VerdictMemoryLimit
			if timeSpent >= limits.TimeSeconds*0.99 {
				verdict = contracts.VerdictTimeLimit
			}
			return ExecutionResult{Success: false, Verdict: verdict, ReturnCode: exitCode, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
		}
		if isMemoryLimitExceeded(program.Language, stderrText) {
			return ExecutionResult{Success: false, Verdict: contracts.VerdictMemoryLimit, ReturnCode: exitCode, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
		}
		return ExecutionResult{Success: false, Verdict: contracts.VerdictRuntimeError, ReturnCode: exitCode, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
	}
	return ExecutionResult{Success: true, Verdict: contracts.VerdictAccepted, ReturnCode: 0, Stdout: stdoutText, Stderr: stderrText, Time: timeSpent}
}

func RunChecker(ctx context.Context, checker CompiledProgram, testdata, participantOutput, juryOutput string, limits Limits) ExecutionResult {
	testFilePath, err := writeTempFile(checker.Dir, "input-*.txt", testdata)
	if err != nil {
		return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: err.Error()}
	}
	participantPath, err := writeTempFile(checker.Dir, "participant-*.txt", participantOutput)
	if err != nil {
		_ = os.Remove(testFilePath)
		return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: err.Error()}
	}
	juryPath, err := writeTempFile(checker.Dir, "jury-*.txt", juryOutput)
	if err != nil {
		_ = os.Remove(testFilePath)
		_ = os.Remove(participantPath)
		return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: err.Error()}
	}
	resultFile, err := os.CreateTemp(checker.Dir, "result-*.txt")
	if err != nil {
		for _, path := range []string{testFilePath, participantPath, juryPath} {
			_ = os.Remove(path)
		}
		return ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -102, Stderr: err.Error()}
	}
	resultPath := resultFile.Name()
	_ = resultFile.Close()
	defer func() {
		for _, path := range []string{testFilePath, participantPath, juryPath, resultPath} {
			_ = os.Remove(path)
		}
	}()
	result := Run(ctx, checker, "", []string{testFilePath, participantPath, juryPath, resultPath}, limits)
	if data, err := os.ReadFile(resultPath); err == nil {
		result.Stdout = string(data)
	}
	if result.ReturnCode == 1 || result.ReturnCode == 2 {
		result.Success = true
		result.Verdict = contracts.VerdictWrongAnswer
	}
	return result
}

func writeTempFile(dir, pattern, content string) (string, error) {
	file, err := os.CreateTemp(dir, pattern)
	if err != nil {
		return "", err
	}
	path := file.Name()
	if _, err := file.WriteString(content); err != nil {
		_ = file.Close()
		_ = os.Remove(path)
		return "", err
	}
	if err := file.Close(); err != nil {
		_ = os.Remove(path)
		return "", err
	}
	return path, nil
}

func CleanStdout(output string, trailingNewline string) string {
	trimmed := strings.TrimRight(output, "\n\r\t ")
	if trimmed == "" {
		if trailingNewline == "always" {
			return "\n"
		}
		return ""
	}
	lines := strings.Split(trimmed, "\n")
	for i, line := range lines {
		lines[i] = strings.TrimRight(line, " \t\r")
	}
	cleaned := strings.Join(lines, "\n")
	if trailingNewline == "always" {
		return cleaned + "\n"
	}
	return cleaned
}

func CompareOutput(a, b string) bool {
	a = strings.TrimRight(a, "\n\r\t ")
	b = strings.TrimRight(b, "\n\r\t ")
	if strings.ReplaceAll(a, "\n", " ") == strings.ReplaceAll(b, "\n", " ") {
		return true
	}
	return strings.ReplaceAll(a, " \n", "\n") == strings.ReplaceAll(b, " \n", "\n")
}

func ShortenPathsToFilenames(s string) string {
	if s == "" {
		return ""
	}
	return tmpPathRegex.ReplaceAllString(s, `$1`)
}

var tmpPathRegex = regexp.MustCompile(`/tmp/.*/([A-Za-z]+\.[a-z]{1,3})`)

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

func normalizeLimits(requested, fallback Limits) Limits {
	if requested.TimeSeconds == 0 {
		requested.TimeSeconds = fallback.TimeSeconds
	}
	if requested.MemoryMB == 0 {
		requested.MemoryMB = fallback.MemoryMB
	}
	if requested.StdoutBytes == 0 {
		requested.StdoutBytes = fallback.StdoutBytes
	}
	if requested.StderrBytes == 0 {
		requested.StderrBytes = fallback.StderrBytes
	}
	defaults := DefaultRunLimits()
	if requested.TimeSeconds == 0 {
		requested.TimeSeconds = defaults.TimeSeconds
	}
	if requested.MemoryMB == 0 {
		requested.MemoryMB = defaults.MemoryMB
	}
	if requested.StdoutBytes == 0 {
		requested.StdoutBytes = defaults.StdoutBytes
	}
	if requested.StderrBytes == 0 {
		requested.StderrBytes = defaults.StderrBytes
	}
	return requested
}

func virtualMemoryLimitMB(language contracts.Language, requestedMB int) int {
	switch language {
	case contracts.LanguageCpp23, contracts.LanguageCpp20, contracts.LanguageCpp17, contracts.LanguageCpp14, contracts.LanguageC11, contracts.LanguageC99, contracts.LanguageRust2021:
		return atLeast(requestedMB, minNativeVirtualMemoryMB)
	default:
		return requestedMB
	}
}

func exitCodeOf(err error) int {
	if err == nil {
		return 0
	}
	if exitErr, ok := err.(*exec.ExitError); ok {
		return exitErr.ExitCode()
	}
	return -1
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
	return append(env, extra...)
}

func atLeast(value, minimum int) int {
	if value < minimum {
		return minimum
	}
	return value
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

func RoundSeconds(d time.Duration) float64 {
	return float64(d.Milliseconds()) / 1000.0
}
