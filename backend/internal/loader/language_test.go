package loader

import (
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestInferLanguageSupportsKnownExtensions(t *testing.T) {
	tests := []struct {
		filename string
		want     contracts.Language
	}{
		{filename: "correct.cpp", want: contracts.LanguageCpp23},
		{filename: "correct.c", want: contracts.LanguageC11},
		{filename: "correct.py", want: contracts.LanguagePython3},
		{filename: "correct.java", want: contracts.LanguageJava},
		{filename: "correct.js", want: contracts.LanguageNodeJS},
		{filename: "correct.go", want: contracts.LanguageGolang},
		{filename: "correct.kt", want: contracts.LanguageKotlin},
		{filename: "correct.rs", want: contracts.LanguageRust2021},
		{filename: "correct.cs", want: contracts.LanguageCSharp},
	}

	for _, tt := range tests {
		t.Run(tt.filename, func(t *testing.T) {
			got, err := InferLanguage(tt.filename, nil)
			if err != nil {
				t.Fatalf("InferLanguage() error = %v", err)
			}
			if got != tt.want {
				t.Fatalf("InferLanguage() = %q, want %q", got, tt.want)
			}
		})
	}
}

func TestInferLanguagePrefersExplicitOverride(t *testing.T) {
	got, err := InferLanguage("correct.py", map[string]string{"correct.py": "pypy3"})
	if err != nil {
		t.Fatalf("InferLanguage() error = %v", err)
	}
	if got != contracts.LanguagePyPy3 {
		t.Fatalf("InferLanguage() = %q, want %q", got, "pypy3")
	}
}
