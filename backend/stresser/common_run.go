package main

import (
	"context"
	"fmt"
	"log/slog"
	"strings"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
)

const (
	python313Command      = executor.Python313Command
	maxRunStdoutBytes     = executor.MaxRunStdoutBytes
	maxRunStderrBytes     = executor.MaxRunStderrBytes
	outputLimitReturnCode = executor.OutputLimitReturnCode
)

type compileResult = executor.CompileResult
type executionResult = executor.ExecutionResult

var languages = executor.SupportedLanguages()

func getCacheDirectory(code string, lang contracts.Language) string {
	return executor.GetCacheDirectory(code, lang)
}

func compileCodeCached(code string, lang contracts.Language) compileResult {
	return executor.Compile(context.Background(), executor.Source{Code: code, Language: lang})
}

func compileAndGetProgram(code string, lang contracts.Language, limits executor.Limits, errorType contracts.ErrorType) (*executor.CompiledProgram, error) {
	result := executor.Compile(context.Background(), executor.Source{Code: code, Language: lang, Limits: limits})
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
		slog.Warn(
			"compile_failed",
			"step", result.StepIndex,
			"exit_code", result.ReturnCode,
			"command", details["command"],
			"stderr", truncateTestcase(result.Stderr, 1200, 20),
			"stdout", truncateTestcase(result.Stdout, 1200, 20),
			"error_type", errorType,
		)
		return nil, NewResponseError(errorType, details)
	}
	return result.Program, nil
}

func runCode(workDir, inputData string, lang contracts.Language, timeLimit float64, memoryLimit int, additionalArgs []string) executionResult {
	limits := executor.Limits{TimeSeconds: timeLimit, MemoryMB: memoryLimit}
	program := executor.CompiledProgram{Dir: workDir, Language: lang, Limits: limits}
	return executor.Run(context.Background(), program, inputData, additionalArgs, limits)
}

func runChecker(workDir, testdata, participantOutput, juryOutput string, timeLimit float64, memoryLimit int) executionResult {
	limits := executor.Limits{TimeSeconds: timeLimit, MemoryMB: memoryLimit}
	program := executor.CompiledProgram{Dir: workDir, Language: contracts.LanguageCpp23, Limits: limits}
	return executor.RunChecker(context.Background(), program, testdata, participantOutput, juryOutput, limits)
}

func generateByCaseProvider(caseProvider contracts.CaseProvider, randomSeed int) (string, contracts.GeneratedBy, *executionResult, error) {
	switch caseProvider.Type {
	case contracts.CaseProviderText:
		return executor.CleanStdout(caseProvider.Content, "always"), contracts.GeneratedBy{Stage: caseProvider.Type, ID: caseProvider.ID}, nil, nil
	case contracts.CaseProviderGenerator, contracts.CaseProviderSinglegen:
		limits := executor.Limits{TimeSeconds: 2, MemoryMB: 1024}
		compiled, err := compileAndGetProgram(caseProvider.Code, caseProvider.Language, limits, contracts.ErrorTypeGeneratorCompilationFailed)
		if err != nil {
			return "", contracts.GeneratedBy{}, nil, err
		}
		args := []string{}
		generatedBy := contracts.GeneratedBy{Stage: caseProvider.Type, ID: caseProvider.ID}
		if caseProvider.Type == contracts.CaseProviderGenerator {
			seed := fmt.Sprintf("%d", randomSeed)
			args = []string{seed}
			generatedBy.Seed = stringPtr(seed)
		}
		execution := executor.Run(context.Background(), *compiled, "", args, limits)
		if !execution.Success {
			return "", contracts.GeneratedBy{}, &execution, nil
		}
		return executor.CleanStdout(execution.Stdout, "always"), generatedBy, nil, nil
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

	correctExecution := executor.Run(context.Background(), correctCode, testcase, nil, correctCode.Limits)
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

	targetExecution := executor.Run(context.Background(), targetCode, testcase, nil, targetCode.Limits)
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
		cleanCorrect := executor.CleanStdout(correctExecution.Stdout, "no")
		cleanTarget := executor.CleanStdout(targetExecution.Stdout, "no")
		checkerExecution := executor.RunChecker(context.Background(), *checkerCode, testcase, cleanTarget, cleanCorrect, checkerCode.Limits)
		if checkerExecution.Success {
			runSummary = targetRun{
				Verdict:       checkerExecution.Verdict,
				TargetOutput:  targetExecution.Stdout,
				CheckerOutput: checkerExecution.Stdout,
				Stderr:        targetExecution.Stderr,
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
		if executor.CompareOutput(targetExecution.Stdout, correctExecution.Stdout) {
			verdict = contracts.VerdictAccepted
		}
		runSummary = targetRun{
			Verdict:      verdict,
			TargetOutput: targetExecution.Stdout,
			Time:         targetExecution.Time,
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
	return executor.RoundSeconds(d)
}
