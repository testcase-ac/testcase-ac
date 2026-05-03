package main

import (
	"slices"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
)

type CodeFile = loader.CodeFile
type TestcaseFile = loader.TestcaseFile
type Problem = loader.Problem
type TypeMetadata = loader.TypeMetadata
type TypeMetadataSegment = loader.TypeMetadataSegment
type TypeMetadataSegmentLabel = loader.TypeMetadataSegmentLabel

func BuildCatalog(testcaseRoot string) (map[[2]string]Problem, error) {
	return loader.BuildCatalog(testcaseRoot)
}

func BuildTypeMetadata(testcaseRoot string) (map[string]TypeMetadata, error) {
	return loader.BuildTypeMetadata(testcaseRoot)
}

func sortProblemSummaries(items []ProblemSummary) {
	slices.SortFunc(items, func(a, b ProblemSummary) int {
		if a.ProblemType != b.ProblemType {
			return strings.Compare(a.ProblemType, b.ProblemType)
		}
		return loader.CompareExternalID(a.ExternalID, b.ExternalID)
	})
}

func sortProblemTypeSummaries(items []ProblemTypeSummary) {
	slices.SortFunc(items, func(a, b ProblemTypeSummary) int {
		aLabel := a.ProblemType
		if a.Label != nil {
			aLabel = *a.Label
		}
		bLabel := b.ProblemType
		if b.Label != nil {
			bLabel = *b.Label
		}
		if compared := strings.Compare(aLabel, bLabel); compared != 0 {
			return compared
		}
		return strings.Compare(a.ProblemType, b.ProblemType)
	})
}
