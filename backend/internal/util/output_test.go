package util

import "testing"

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
				got := CleanStdout(tt.input, tt.trailingNewline)
				if got != tt.want {
					t.Fatalf("CleanStdout(%q, %q) = %q, want %q", tt.input, tt.trailingNewline, got, tt.want)
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
				got := CleanStdout(tt.input, tt.trailingNewline)
				if got != tt.want {
					t.Fatalf("CleanStdout(%q, %q) = %q, want %q", tt.input, tt.trailingNewline, got, tt.want)
				}
			})
		}
	})
}

func TestCompareOutput(t *testing.T) {
	// Compare outputs in BOJ style:
	// - "space" and "newline" are equal
	// - "newline" and "space + newline" are equal
	// - but "space" and "space + newline" are not equal
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
				if !CompareOutput(sample, candidate) {
					t.Fatalf("CompareOutput(%q, %q) = false, want true", sample, candidate)
				}
				if !CompareOutput(candidate, sample) {
					t.Fatalf("CompareOutput(%q, %q) = false, want true", candidate, sample)
				}
			})
		}

		for _, candidate := range unequalCases {
			t.Run("unequal "+candidate, func(t *testing.T) {
				if CompareOutput(sample, candidate) {
					t.Fatalf("CompareOutput(%q, %q) = true, want false", sample, candidate)
				}
				if CompareOutput(candidate, sample) {
					t.Fatalf("CompareOutput(%q, %q) = true, want false", candidate, sample)
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
				if !CompareOutput(sample, candidate) {
					t.Fatalf("CompareOutput(%q, %q) = false, want true", sample, candidate)
				}
				if !CompareOutput(candidate, sample) {
					t.Fatalf("CompareOutput(%q, %q) = false, want true", candidate, sample)
				}
			})
		}

		for _, candidate := range unequalCases {
			t.Run("unequal "+candidate, func(t *testing.T) {
				if CompareOutput(sample, candidate) {
					t.Fatalf("CompareOutput(%q, %q) = true, want false", sample, candidate)
				}
				if CompareOutput(candidate, sample) {
					t.Fatalf("CompareOutput(%q, %q) = true, want false", candidate, sample)
				}
			})
		}
	})
}
