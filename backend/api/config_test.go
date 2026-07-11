package main

import "testing"

func TestLoadSettingsAllowsMissingAuthorIndexPath(t *testing.T) {
	t.Setenv("AUTHOR_INDEX_PATH", "")

	settings, err := LoadSettings()
	if err != nil {
		t.Fatal(err)
	}
	if settings.AuthorIndexPath != "" {
		t.Fatalf("AuthorIndexPath = %q, want empty", settings.AuthorIndexPath)
	}
}
