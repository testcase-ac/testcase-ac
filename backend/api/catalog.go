package main

import (
	"slices"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
)

type CodeFile = loader.CodeFile
type TestcaseFile = loader.TestcaseFile
type Problem = loader.Problem

func BuildCatalog(testcaseRoot string) (map[[2]string]Problem, error) {
	return loader.BuildCatalog(testcaseRoot)
}

func inferLanguage(filename string, overrides map[string]string) (contracts.Language, error) {
	return loader.InferLanguage(filename, overrides)
}

func sortProblemSummaries(items []ProblemSummary) {
	slices.SortFunc(items, func(a, b ProblemSummary) int {
		if a.ProblemType != b.ProblemType {
			return strings.Compare(a.ProblemType, b.ProblemType)
		}
		return loader.CompareExternalID(a.ExternalID, b.ExternalID)
	})
}
