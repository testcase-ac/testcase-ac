package main

import (
	"context"
	"fmt"
	"log/slog"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/util"
)

type executionResult = executor.ExecutionResult

func (s stresser) compileAndGetProgram(code string, lang contracts.Language, limits executor.Limits, errorType contracts.ErrorType) (*executor.CompiledProgram, error) {
	result := s.compile(context.Background(), executor.Source{Code: code, Language: lang, Limits: limits})
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

func (s stresser) stressTestIteration(targetCode, correctCode compiledProgram, checkerCode *compiledProgram, caseProvider compiledCaseProvider, randomSeed int) (stressIteration, error) {
	testcase, generatedBy, generateError, err := s.generateCaseProvider(caseProvider, randomSeed)
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

	correctExecution := s.run(context.Background(), correctCode, testcase, nil, correctCode.Limits)
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

	targetExecution := s.run(context.Background(), targetCode, testcase, nil, targetCode.Limits)
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
		checkerExecution := s.runChecker(context.Background(), *checkerCode, testcase, cleanTarget, cleanCorrect, checkerCode.Limits)
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
