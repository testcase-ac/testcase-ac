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
		report := verifyProblem(path)
		if report.Status != verify.StatusOK {
			exitCode = 1
		}
		reports = append(reports, report)
	}

	writeReports(reports, *jsonOutput)
	os.Exit(exitCode)
}

func verifyProblem(problemPath string) verify.VerifyReport {
	problem, err := loader.LoadProblem(problemPath, loader.Options{AllowUnknownFiles: true})
	if err != nil {
		return verify.VerifyReport{
			ProblemPath: problemPath,
			Status:      verify.StatusFailed,
			Findings: []verify.Finding{
				{
					Severity: verify.SeverityError,
					Stage:    verify.StageStatic,
					Message:  fmt.Sprintf("load problem: %v", err),
				},
			},
		}
	}

	report := verify.VerifyProblem(context.Background(), problem)
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
	fmt.Printf("Status: %s\n", report.Status)
	fmt.Printf("Sampled cases: %d\n", report.SampledCasesCount)
	fmt.Printf("Runtime: %.3fs\n", report.RuntimeSeconds)
	if len(report.Findings) == 0 {
		fmt.Println("Findings: none")
		return
	}
	fmt.Println("Findings:")
	for _, finding := range report.Findings {
		location := finding.Filename
		if finding.Seed != nil {
			if location != "" {
				location += " "
			}
			location += fmt.Sprintf("seed=%d", *finding.Seed)
		}
		if location == "" {
			location = "(problem)"
		}
		fmt.Printf("- [%s] %s %s: %s\n", finding.Severity, finding.Stage, location, finding.Message)
		if finding.Stderr != "" {
			fmt.Printf("  stderr: %s\n", oneLine(finding.Stderr))
		}
		if finding.Stdout != "" {
			fmt.Printf("  stdout: %s\n", oneLine(finding.Stdout))
		}
	}
}

func oneLine(value string) string {
	value = strings.ReplaceAll(strings.TrimSpace(value), "\n", `\n`)
	if len(value) > 300 {
		return value[:300] + "...(truncated)"
	}
	return value
}
