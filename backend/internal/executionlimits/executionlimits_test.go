package executionlimits

import (
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestAdjustedAppliesBojLanguagePolicies(t *testing.T) {
	tests := []struct {
		name         string
		lang         contracts.Language
		timeLimitMS  int
		memoryLimit  int
		wantTimeS    float64
		wantMemoryMB int
	}{
		{name: "nodejs", lang: "nodejs", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 8, wantMemoryMB: 256},
		{name: "csharp", lang: "csharp", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 5, wantMemoryMB: 272},
		{name: "python3", lang: "python3", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 8, wantMemoryMB: 288},
		{name: "pypy3", lang: "pypy3", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 8, wantMemoryMB: 384},
		{name: "golang", lang: "golang", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 4, wantMemoryMB: 640},
		{name: "rust2021", lang: "rust2021", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 2, wantMemoryMB: 144},
		{name: "cpp23 default", lang: "cpp23", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 2, wantMemoryMB: 128},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			gotTimeS, gotMemoryMB := Adjusted("boj", tt.lang, tt.timeLimitMS, tt.memoryLimit)
			if gotTimeS != tt.wantTimeS {
				t.Fatalf("Adjusted() time = %.3f, want %.3f", gotTimeS, tt.wantTimeS)
			}
			if gotMemoryMB != tt.wantMemoryMB {
				t.Fatalf("Adjusted() memory = %d, want %d", gotMemoryMB, tt.wantMemoryMB)
			}
		})
	}
}

func TestAdjustedLeavesNonBojLimitsUntouched(t *testing.T) {
	gotTimeS, gotMemoryMB := Adjusted("cf", contracts.LanguageNodeJS, 2000, 128)
	if gotTimeS != 2 {
		t.Fatalf("Adjusted() time = %.3f, want 2", gotTimeS)
	}
	if gotMemoryMB != 128 {
		t.Fatalf("Adjusted() memory = %d, want 128", gotMemoryMB)
	}
}
