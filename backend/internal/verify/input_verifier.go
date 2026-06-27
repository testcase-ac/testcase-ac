package verify

// This file owns verification after a sampled input exists: validator
// acceptance, reference-output selection, correct-solution consistency, and
// rejected-solution proof.

import (
	"context"
	"fmt"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
	"github.com/testcase-ac/testcase-ac/backend/internal/util"
)

type inputVerifier struct {
	runner            verifier
	report            *VerifyReport
	problem           loader.Problem
	compiled          compiledFiles
	options           VerifyOptions
	validator         *executor.CompiledProgram
	checker           *executor.CompiledProgram
	answersByProvider map[string]*loader.AnswerFile
	rejected          rejectedSolutionStates
}

type referenceOutput struct {
	text             string
	usableForJudging bool
}

type rejectedSolutionState int

const (
	rejectedSolutionUnseen rejectedSolutionState = iota
	rejectedSolutionAttemptedWithoutProof
	rejectedSolutionHasProof
)

type rejectedSolutionStates map[string]rejectedSolutionState

func newInputVerifier(v verifier, report *VerifyReport, problem loader.Problem, compiled compiledFiles, options VerifyOptions) inputVerifier {
	inputs := inputVerifier{
		runner:            v,
		report:            report,
		problem:           problem,
		compiled:          compiled,
		options:           options,
		answersByProvider: answerFilesByProvider(problem.AnswerFiles),
		rejected:          newRejectedSolutionStates(problem, compiled, options),
	}
	if problem.Validator != nil {
		inputs.validator = compiled[problem.Validator.Filename]
	}
	if problem.Checker != nil {
		inputs.checker = compiled[problem.Checker.Filename]
	}
	return inputs
}

// verify checks one provider-backed input after verify.go has sampled it.
func (iv *inputVerifier) verify(ctx context.Context, input testInput) {
	iv.report.SampledCasesCount++
	if input.Answer == nil {
		input.Answer = iv.answersByProvider[input.Filename]
	}
	if iv.validator == nil {
		return
	}
	result := iv.runner.run(ctx, *iv.validator, input.Content, nil, helperLimits())
	if !result.Success || result.ReturnCode != 0 {
		iv.report.addExecution(StageValidator, input.Filename, input.Seed, "validator rejected testcase", result)
		return
	}
	if iv.options.Mode == VerifyModeValidateInputs {
		return
	}
	reference := iv.verifyCorrectConsistency(ctx, input)
	if reference.usableForJudging {
		iv.rejected.verifyInput(ctx, iv, input, reference.text)
	}
}

// verifyOutputOnly checks the single implicit empty input for output-only problems.
func (iv *inputVerifier) verifyOutputOnly(ctx context.Context) {
	if iv.options.Mode == VerifyModeValidateInputs || len(iv.problem.CorrectCodes) == 0 {
		return
	}
	iv.report.SampledCasesCount++
	input := testInput{
		Content:  "",
		Filename: contracts.OutputOnlyEmptyInputID,
	}
	reference := iv.verifyCorrectConsistency(ctx, input)
	if reference.usableForJudging {
		iv.rejected.verifyInput(ctx, iv, input, reference.text)
	}
}

func (iv *inputVerifier) reportRejectedSolutionsAcceptedByAllCheckedInputs() {
	iv.rejected.addMissingFindings(iv.report, iv.problem)
}

func newRejectedSolutionStates(problem loader.Problem, compiled compiledFiles, options VerifyOptions) rejectedSolutionStates {
	if options.Mode == VerifyModeValidateInputs {
		return rejectedSolutionStates{}
	}
	states := rejectedSolutionStates{}
	for _, file := range problem.RejectedCodes {
		if compiled[file.Filename] != nil {
			states[file.Filename] = rejectedSolutionUnseen
		}
	}
	return states
}

func (states rejectedSolutionStates) verifyInput(ctx context.Context, iv *inputVerifier, input testInput, jury string) {
	if len(states) == 0 {
		return
	}
	for _, rejected := range iv.problem.RejectedCodes {
		state, ok := states[rejected.Filename]
		if !ok || state == rejectedSolutionHasProof {
			continue
		}
		program := iv.compiled[rejected.Filename]
		if program == nil {
			continue
		}
		states.setAttempted(rejected.Filename)
		result := iv.runner.run(ctx, *program, input.Content, nil, limitsFor(iv.problem, rejected.Language))
		if !result.Success || result.Verdict != contracts.VerdictAccepted {
			states.setProved(rejected.Filename)
			continue
		}
		output := util.CleanStdout(result.Stdout, "no")
		if iv.checker != nil {
			result := iv.runner.runChecker(ctx, *iv.checker, input.Content, output, jury, helperLimits())
			if !result.Success || result.Verdict != contracts.VerdictAccepted {
				states.setProved(rejected.Filename)
			}
		} else if !util.CompareOutput(output, jury) {
			states.setProved(rejected.Filename)
		}
	}
}

func (states rejectedSolutionStates) setAttempted(filename string) {
	if states[filename] == rejectedSolutionUnseen {
		states[filename] = rejectedSolutionAttemptedWithoutProof
	}
}

func (states rejectedSolutionStates) setProved(filename string) {
	states[filename] = rejectedSolutionHasProof
}

func (states rejectedSolutionStates) addMissingFindings(report *VerifyReport, problem loader.Problem) {
	if len(states) == 0 {
		return
	}
	for _, rejected := range problem.RejectedCodes {
		if states[rejected.Filename] != rejectedSolutionAttemptedWithoutProof {
			continue
		}
		report.AddFinding(SeverityError, StageRejected, rejected.Filename, nil, "rejected solution was accepted by all sampled case providers", "", "")
	}
}

// verifyCorrectConsistency records correct-solution findings and returns output
// that rejected solutions can be judged against when consistency checks pass.
func (iv *inputVerifier) verifyCorrectConsistency(ctx context.Context, input testInput) referenceOutput {
	if len(iv.problem.CorrectCodes) == 0 {
		return referenceOutput{}
	}
	if input.Answer != nil {
		text, usableForJudging := iv.verifyInputAgainstAnswerFile(ctx, input)
		return referenceOutput{text: text, usableForJudging: usableForJudging}
	}
	text, usableForJudging := iv.verifyInputAgainstPrimaryCorrect(ctx, input)
	return referenceOutput{text: text, usableForJudging: usableForJudging}
}

func (iv *inputVerifier) verifyInputAgainstAnswerFile(ctx context.Context, input testInput) (string, bool) {
	jury := util.CleanStdout(input.Answer.Content, "no")
	usableForJudging := true
	if iv.checker != nil {
		result := iv.runner.runChecker(ctx, *iv.checker, input.Content, jury, jury, helperLimits())
		if !result.Success || result.Verdict != contracts.VerdictAccepted {
			iv.report.addInputExecution(StageChecker, iv.problem.Checker.Filename, input, fmt.Sprintf("checker rejected answer file %s against itself", input.Answer.Filename), result)
			usableForJudging = false
		}
	}

	for _, correct := range iv.problem.CorrectCodes {
		program := iv.compiled[correct.Filename]
		if program == nil {
			continue
		}
		result := iv.runner.run(ctx, *program, input.Content, nil, limitsFor(iv.problem, correct.Language))
		if !result.Success {
			iv.report.addInputExecution(StageCorrectConsistency, correct.Filename, input, "correct solution failed on test input", result)
			usableForJudging = false
			continue
		}
		output := util.CleanStdout(result.Stdout, "no")
		if iv.checker != nil {
			result := iv.runner.runChecker(ctx, *iv.checker, input.Content, output, jury, helperLimits())
			if !result.Success || result.Verdict != contracts.VerdictAccepted {
				iv.report.addInputExecution(StageCorrectConsistency, correct.Filename, input, fmt.Sprintf("correct solution output was rejected by checker against answer file %s", input.Answer.Filename), result)
				usableForJudging = false
			}
		} else if !util.CompareOutput(output, jury) {
			iv.report.addFinding(SeverityError, StageCorrectConsistency, correct.Filename, input.Filename, input.Seed, fmt.Sprintf("correct solution output differs from answer file %s", input.Answer.Filename), output, jury)
			usableForJudging = false
		}
	}
	return jury, usableForJudging
}

func (iv *inputVerifier) verifyInputAgainstPrimaryCorrect(ctx context.Context, input testInput) (string, bool) {
	var jury string
	primaryOK := false
	primaryCode := iv.problem.CorrectCodes[0]
	primary := iv.compiled[primaryCode.Filename]
	if primary != nil {
		primaryRun := iv.runner.run(ctx, *primary, input.Content, nil, limitsFor(iv.problem, primaryCode.Language))
		if !primaryRun.Success {
			iv.report.addInputExecution(StageCorrectConsistency, primaryCode.Filename, input, "correct solution failed on test input", primaryRun)
		} else {
			jury = util.CleanStdout(primaryRun.Stdout, "no")
			primaryOK = true
		}
	}

	usableForJudging := primaryOK
	if primaryOK && iv.checker != nil {
		result := iv.runner.runChecker(ctx, *iv.checker, input.Content, jury, jury, helperLimits())
		if !result.Success || result.Verdict != contracts.VerdictAccepted {
			iv.report.addInputExecution(StageChecker, iv.problem.Checker.Filename, input, "checker rejected identical participant and jury output", result)
			usableForJudging = false
		}
	}

	for i := 1; i < len(iv.problem.CorrectCodes); i++ {
		correct := iv.problem.CorrectCodes[i]
		program := iv.compiled[correct.Filename]
		if program == nil {
			continue
		}
		result := iv.runner.run(ctx, *program, input.Content, nil, limitsFor(iv.problem, correct.Language))
		if !result.Success {
			iv.report.addInputExecution(StageCorrectConsistency, correct.Filename, input, "correct solution failed on test input", result)
			continue
		}
		if !primaryOK {
			continue
		}
		output := util.CleanStdout(result.Stdout, "no")
		if iv.checker != nil {
			result := iv.runner.runChecker(ctx, *iv.checker, input.Content, output, jury, helperLimits())
			if !result.Success || result.Verdict != contracts.VerdictAccepted {
				iv.report.addInputExecution(StageCorrectConsistency, correct.Filename, input, "correct solution output was rejected by checker", result)
			}
		} else if !util.CompareOutput(output, jury) {
			iv.report.addFinding(SeverityError, StageCorrectConsistency, correct.Filename, input.Filename, input.Seed, "correct solution output differs from primary correct solution", output, jury)
		}
	}
	return jury, usableForJudging
}

func answerFilesByProvider(answerFiles []loader.AnswerFile) map[string]*loader.AnswerFile {
	out := make(map[string]*loader.AnswerFile, len(answerFiles))
	for i := range answerFiles {
		answer := &answerFiles[i]
		out[answer.TargetProviderFilename] = answer
	}
	return out
}
