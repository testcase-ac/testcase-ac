package main

import (
	"context"
	"encoding/json"
	"flag"
	"fmt"
	"os"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
	"github.com/testcase-ac/testcase-ac/backend/internal/verify"
)

func main() {
	problemPath := flag.String("problem", "", "path to testcase/<type>/<id> problem directory")
	jsonOutput := flag.Bool("json", false, "print JSON report")
	validateInputs := flag.Bool("validate-inputs", false, "run case providers and validate produced inputs without output judging")
	flag.Parse()

	problemPaths := flag.Args()
	if strings.TrimSpace(*problemPath) != "" {
		problemPaths = append([]string{*problemPath}, problemPaths...)
	}
	if len(problemPaths) == 0 {
		fmt.Fprintln(os.Stderr, "--problem or at least one problem path argument is required")
		os.Exit(2)
	}

	reports := make([]verify.VerifyReport, 0, len(problemPaths))
	exitCode := 0
	for _, path := range problemPaths {
		report := verifyProblem(path, verifyOptions(*validateInputs))
		if report.HasErrorFinding {
			exitCode = 1
		}
		reports = append(reports, report)
	}

	writeReports(reports, *jsonOutput)
	os.Exit(exitCode)
}

func verifyOptions(validateInputs bool) verify.VerifyOptions {
	if validateInputs {
		return verify.VerifyOptions{Mode: verify.VerifyModeValidateInputs}
	}
	return verify.VerifyOptions{}
}

func verifyProblem(problemPath string, options verify.VerifyOptions) verify.VerifyReport {
	problem, err := loader.LoadProblem(problemPath, loader.Options{AllowUnknownFiles: true})
	if err != nil {
		report := verify.VerifyReport{
			ProblemPath: problemPath,
		}
		report.AddFinding(verify.SeverityError, verify.StageStatic, "", nil, fmt.Sprintf("load problem: %v", err), "", "")
		return report
	}

	report := verify.VerifyProblemWithOptions(context.Background(), problem, options)
	report.ProblemPath = problemPath
	return report
}

func writeReports(reports []verify.VerifyReport, jsonOutput bool) {
	if jsonOutput {
		encoder := json.NewEncoder(os.Stdout)
		encoder.SetIndent("", "  ")
		var payload any = reports
		if len(reports) == 1 {
			payload = reports[0]
		}
		if err := encoder.Encode(payload); err != nil {
			fmt.Fprintf(os.Stderr, "encode report: %v\n", err)
			os.Exit(1)
		}
		return
	}
	for i, report := range reports {
		if i > 0 {
			fmt.Println()
		}
		printTextReport(report)
	}
}

func printTextReport(report verify.VerifyReport) {
	if report.ProblemPath != "" {
		fmt.Printf("Path: %s\n", report.ProblemPath)
	}
	fmt.Printf("Problem: %s/%s\n", report.ProblemType, report.ExternalID)
	fmt.Printf("Status: %s\n", reportStatus(report))
	fmt.Printf("Sampled cases: %d\n", report.SampledCasesCount)
	fmt.Printf("Runtime: %.3fs\n", report.RuntimeSeconds)
	if len(report.Findings) == 0 {
		fmt.Println("Findings: none")
		return
	}
	fmt.Println("Findings:")
	for _, finding := range report.Findings {
		location := findingLocation(finding)
		fmt.Printf("- [%s] %s %s: %s\n", finding.Severity, finding.Stage, location, finding.Message)
		if finding.Stderr != "" {
			fmt.Printf("  stderr: %s\n", oneLine(finding.Stderr))
		}
		if finding.Stdout != "" {
			fmt.Printf("  stdout: %s\n", oneLine(finding.Stdout))
		}
	}
}

func findingLocation(finding verify.Finding) string {
	parts := []string{}
	if finding.Filename != "" {
		parts = append(parts, finding.Filename)
	}
	if finding.InputFilename != "" {
		parts = append(parts, "input="+finding.InputFilename)
	}
	if finding.Seed != nil {
		parts = append(parts, fmt.Sprintf("seed=%d", *finding.Seed))
	}
	if len(parts) == 0 {
		return "(problem)"
	}
	return strings.Join(parts, " ")
}

func reportStatus(report verify.VerifyReport) string {
	if report.HasErrorFinding {
		return "failed"
	}
	return "ok"
}

func oneLine(value string) string {
	value = strings.ReplaceAll(strings.TrimSpace(value), "\n", `\n`)
	if len(value) > 300 {
		return value[:300] + "...(truncated)"
	}
	return value
}
