package main

import (
	"os/exec"
	"testing"
)

func requireCommands(t *testing.T, names ...string) {
	t.Helper()
	for _, name := range names {
		if _, err := exec.LookPath(name); err != nil {
			t.Fatalf("required command %q is not available; run ./tests/stresser/run_test.sh for the Docker-backed stresser test environment", name)
		}
	}
}
