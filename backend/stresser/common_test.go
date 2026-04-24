package main

import (
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestTextWithMetadata(t *testing.T) {
	t.Run("untruncated metadata", func(t *testing.T) {
		got := textWithMetadata("a\nb\n", 100, 10)
		if got.Text != "a\nb\n" {
			t.Fatalf("Text = %q, want %q", got.Text, "a\nb\n")
		}
		if got.Metadata.CharacterCount != 4 {
			t.Fatalf("CharacterCount = %d, want 4", got.Metadata.CharacterCount)
		}
		if got.Metadata.LineCount != 2 {
			t.Fatalf("LineCount = %d, want 2", got.Metadata.LineCount)
		}
		if got.Metadata.Truncated {
			t.Fatalf("Truncated = true, want false")
		}
	})

	t.Run("character truncation", func(t *testing.T) {
		got := textWithMetadata("abcdef", 3, 10)
		if got.Text != "abc" {
			t.Fatalf("Text = %q, want %q", got.Text, "abc")
		}
		if got.Metadata.CharacterCount != 6 {
			t.Fatalf("CharacterCount = %d, want 6", got.Metadata.CharacterCount)
		}
		if got.Metadata.LineCount != 1 {
			t.Fatalf("LineCount = %d, want 1", got.Metadata.LineCount)
		}
		if !got.Metadata.Truncated {
			t.Fatalf("Truncated = false, want true")
		}
		if got.Metadata.TruncatedBy == nil || *got.Metadata.TruncatedBy != contracts.TruncationKindCharacter {
			t.Fatalf("TruncatedBy = %v, want character", got.Metadata.TruncatedBy)
		}
		if got.Metadata.TruncatedAtCharacter == nil || *got.Metadata.TruncatedAtCharacter != 3 {
			t.Fatalf("TruncatedAtCharacter = %v, want 3", got.Metadata.TruncatedAtCharacter)
		}
		if got.Metadata.TruncatedAtLine != nil {
			t.Fatalf("TruncatedAtLine = %v, want nil", got.Metadata.TruncatedAtLine)
		}
	})

	t.Run("line truncation", func(t *testing.T) {
		got := textWithMetadata("a\nb\nc\n", 100, 2)
		if got.Text != "a\nb" {
			t.Fatalf("Text = %q, want %q", got.Text, "a\nb")
		}
		if got.Metadata.CharacterCount != 6 {
			t.Fatalf("CharacterCount = %d, want 6", got.Metadata.CharacterCount)
		}
		if got.Metadata.LineCount != 3 {
			t.Fatalf("LineCount = %d, want 3", got.Metadata.LineCount)
		}
		if !got.Metadata.Truncated {
			t.Fatalf("Truncated = false, want true")
		}
		if got.Metadata.TruncatedBy == nil || *got.Metadata.TruncatedBy != contracts.TruncationKindLine {
			t.Fatalf("TruncatedBy = %v, want line", got.Metadata.TruncatedBy)
		}
		if got.Metadata.TruncatedAtLine == nil || *got.Metadata.TruncatedAtLine != 2 {
			t.Fatalf("TruncatedAtLine = %v, want 2", got.Metadata.TruncatedAtLine)
		}
		if got.Metadata.TruncatedAtCharacter == nil || *got.Metadata.TruncatedAtCharacter != 3 {
			t.Fatalf("TruncatedAtCharacter = %v, want 3", got.Metadata.TruncatedAtCharacter)
		}
	})
}

func TestCleanStdout(t *testing.T) {
	t.Run("basic trailing newline modes", func(t *testing.T) {
		tests := []struct {
			name            string
			input           string
			trailingNewline string
			want            string
		}{
			{
				name:            "no trailing newline default",
				input:           "hello\nworld",
				trailingNewline: "no",
				want:            "hello\nworld",
			},
			{
				name:            "one trailing newline default",
				input:           "hello\nworld\n",
				trailingNewline: "no",
				want:            "hello\nworld",
			},
			{
				name:            "multiple trailing newlines default",
				input:           "hello\nworld\n\n",
				trailingNewline: "no",
				want:            "hello\nworld",
			},
			{
				name:            "always adds newline",
				input:           "hello\nworld",
				trailingNewline: "always",
				want:            "hello\nworld\n",
			},
			{
				name:            "always normalizes to one newline",
				input:           "hello\nworld\n\n",
				trailingNewline: "always",
				want:            "hello\nworld\n",
			},
		}

		for _, tt := range tests {
			t.Run(tt.name, func(t *testing.T) {
				got := cleanStdout(tt.input, tt.trailingNewline)
				if got != tt.want {
					t.Fatalf("cleanStdout(%q, %q) = %q, want %q", tt.input, tt.trailingNewline, got, tt.want)
				}
			})
		}
	})

	t.Run("edge cases", func(t *testing.T) {
		tests := []struct {
			name            string
			input           string
			trailingNewline string
			want            string
		}{
			{
				name:            "empty default",
				input:           "",
				trailingNewline: "no",
				want:            "",
			},
			{
				name:            "empty always",
				input:           "",
				trailingNewline: "always",
				want:            "\n",
			},
			{
				name:            "single newline default",
				input:           "\n",
				trailingNewline: "no",
				want:            "",
			},
			{
				name:            "single newline always",
				input:           "\n",
				trailingNewline: "always",
				want:            "\n",
			},
			{
				name:            "multiple internal newlines",
				input:           "hello\n\nworld\n\n",
				trailingNewline: "no",
				want:            "hello\n\nworld",
			},
			{
				name:            "multiple internal newlines always",
				input:           "hello\n\nworld\n\n",
				trailingNewline: "always",
				want:            "hello\n\nworld\n",
			},
			{
				name:            "trim trailing spaces per line",
				input:           "  hello  \n  world  \n",
				trailingNewline: "no",
				want:            "  hello\n  world",
			},
			{
				name:            "trim trailing spaces per line always",
				input:           "  hello  \n  world  \n",
				trailingNewline: "always",
				want:            "  hello\n  world\n",
			},
		}

		for _, tt := range tests {
			t.Run(tt.name, func(t *testing.T) {
				got := cleanStdout(tt.input, tt.trailingNewline)
				if got != tt.want {
					t.Fatalf("cleanStdout(%q, %q) = %q, want %q", tt.input, tt.trailingNewline, got, tt.want)
				}
			})
		}
	})
}

func TestCompareOutput(t *testing.T) {
	t.Run("one line cases", func(t *testing.T) {
		sample := "1 2"
		equalCases := []string{
			"1 2",
			"1 2\n",
			"1\n2\n",
		}
		unequalCases := []string{
			"1  2",
			"1 \n2\n",
		}

		for _, candidate := range equalCases {
			t.Run("equal "+candidate, func(t *testing.T) {
				if !compareOutput(sample, candidate) {
					t.Fatalf("compareOutput(%q, %q) = false, want true", sample, candidate)
				}
				if !compareOutput(candidate, sample) {
					t.Fatalf("compareOutput(%q, %q) = false, want true", candidate, sample)
				}
			})
		}

		for _, candidate := range unequalCases {
			t.Run("unequal "+candidate, func(t *testing.T) {
				if compareOutput(sample, candidate) {
					t.Fatalf("compareOutput(%q, %q) = true, want false", sample, candidate)
				}
				if compareOutput(candidate, sample) {
					t.Fatalf("compareOutput(%q, %q) = true, want false", candidate, sample)
				}
			})
		}
	})

	t.Run("multiple line cases", func(t *testing.T) {
		sample := "1 2\n1 2 "
		equalCases := []string{
			"1 2\n1 2",
			"1 2\n1 2 ",
			"1 2 1 2",
			"1\n2 1\n2\n",
			"1 2 \n1 2 ",
		}
		unequalCases := []string{
			"1  2\n1 2 ",
			"1 \n2\n1 2",
			"1 2  \n1 2",
		}

		for _, candidate := range equalCases {
			t.Run("equal "+candidate, func(t *testing.T) {
				if !compareOutput(sample, candidate) {
					t.Fatalf("compareOutput(%q, %q) = false, want true", sample, candidate)
				}
				if !compareOutput(candidate, sample) {
					t.Fatalf("compareOutput(%q, %q) = false, want true", candidate, sample)
				}
			})
		}

		for _, candidate := range unequalCases {
			t.Run("unequal "+candidate, func(t *testing.T) {
				if compareOutput(sample, candidate) {
					t.Fatalf("compareOutput(%q, %q) = true, want false", sample, candidate)
				}
				if compareOutput(candidate, sample) {
					t.Fatalf("compareOutput(%q, %q) = true, want false", candidate, sample)
				}
			})
		}
	})
}
