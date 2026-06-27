package main

import (
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/internal/verify"
)

func TestFindingLocationIncludesInputProvider(t *testing.T) {
	// Given: a correct-consistency finding from a fixed testcase.
	finding := verify.Finding{
		Filename:      "correct_main.cpp",
		InputFilename: "additional_2.in",
	}

	// When: the text report formats the finding location.
	got := findingLocation(finding)

	// Then: the location includes both the failing file and input provider.
	want := "correct_main.cpp input=additional_2.in"
	if got != want {
		t.Fatalf("findingLocation() = %q, want %q", got, want)
	}
}

func TestFindingLocationIncludesGeneratorSeed(t *testing.T) {
	// Given: a correct-consistency finding from a generator output.
	seed := 7
	finding := verify.Finding{
		Filename:      "correct_main.cpp",
		InputFilename: "generator_sample.cpp",
		Seed:          &seed,
	}

	// When: the text report formats the finding location.
	got := findingLocation(finding)

	// Then: the location includes both provider filename and seed.
	want := "correct_main.cpp input=generator_sample.cpp seed=7"
	if got != want {
		t.Fatalf("findingLocation() = %q, want %q", got, want)
	}
}
