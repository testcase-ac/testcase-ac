package main

import (
	"context"
	"errors"
	"fmt"
	"log/slog"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/util"
)

type executionResult = executor.ExecutionResult

var errTotalRuntimeLimitExceeded = errors.New("total runtime limit exceeded")

func (s stresser) compileAndGetProgram(ctx context.Context, code string, lang contracts.Language, limits executor.Limits, errorType contracts.ErrorType) (*compiledProgram, error) {
	if ctx.Err() != nil {
		return nil, compilationTimedOutError(errorType)
	}
	result := s.compile(ctx, executor.Source{Code: code, Language: lang})
	if ctx.Err() != nil {
		return nil, compilationTimedOutError(errorType)
	}
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
	return &compiledProgram{Program: *result.Program, Limits: limits}, nil
}

func compilationTimedOutError(compileErrorType contracts.ErrorType) *ResponseError {
	return NewResponseError(contracts.ErrorTypeCompilationTimedOut, map[string]any{
		"message":          "Compilation did not finish before the total runtime limit.",
		"compileErrorType": compileErrorType,
	})
}

func (s stresser) stressTestIteration(ctx context.Context, targetCode, correctCode compiledProgram, checkerCode *compiledProgram, caseProvider compiledCaseProvider, randomSeed int) (stressIteration, error) {
	testcase, generatedBy, generateError, err := s.generateCaseProvider(ctx, caseProvider, randomSeed)
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

	correctExecution := s.run(ctx, correctCode.Program, testcase, nil, correctCode.Limits)
	if ctx.Err() != nil {
		return stressIteration{}, errTotalRuntimeLimitExceeded
	}
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

	targetExecution := s.run(ctx, targetCode.Program, testcase, nil, targetCode.Limits)
	if ctx.Err() != nil {
		return stressIteration{}, errTotalRuntimeLimitExceeded
	}
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
		cleanCorrect := util.CleanStdout(correctExecution.Stdout, "no")
		cleanTarget := util.CleanStdout(targetExecution.Stdout, "no")
		checkerExecution := s.runChecker(ctx, checkerCode.Program, testcase, cleanTarget, cleanCorrect, checkerCode.Limits)
		if ctx.Err() != nil {
			return stressIteration{}, errTotalRuntimeLimitExceeded
		}
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
		if util.CompareOutput(targetExecution.Stdout, correctExecution.Stdout) {
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
