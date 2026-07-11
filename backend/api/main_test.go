package main

import (
	"os"
	"path/filepath"
	"strings"
	"testing"
)

func TestLoadAuthorIndexUsesConfiguredManifest(t *testing.T) {
	manifestPath := filepath.Join(t.TempDir(), "author-index.json")
	if err := os.WriteFile(manifestPath, []byte(`{"boj/1000/validator.cpp":"alice"}`), 0o644); err != nil {
		t.Fatal(err)
	}

	index, err := loadAuthorIndex(Settings{
		AuthorIndexPath:   manifestPath,
		TestcaseLocalPath: t.TempDir(),
	})
	if err != nil {
		t.Fatal(err)
	}
	if got := index["boj/1000/validator.cpp"]; got != "alice" {
		t.Fatalf("validator author = %q, want alice", got)
	}
}

func TestLoadAuthorIndexRejectsMissingConfiguredManifest(t *testing.T) {
	_, err := loadAuthorIndex(Settings{
		AuthorIndexPath:   filepath.Join(t.TempDir(), "missing.json"),
		TestcaseLocalPath: t.TempDir(),
	})
	if err == nil || !strings.Contains(err.Error(), "read author index") {
		t.Fatalf("loadAuthorIndex() error = %v, want read author index error", err)
	}
}

func TestLoadAuthorIndexReturnsEmptyWithoutManifestOrGit(t *testing.T) {
	index, err := loadAuthorIndex(Settings{TestcaseLocalPath: t.TempDir()})
	if err != nil {
		t.Fatal(err)
	}
	if len(index) != 0 {
		t.Fatalf("len(loadAuthorIndex()) = %d, want 0", len(index))
	}
}
