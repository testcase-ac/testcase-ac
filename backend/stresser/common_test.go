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
