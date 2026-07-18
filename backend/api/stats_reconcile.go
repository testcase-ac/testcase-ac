package main

import (
	"bytes"
	"context"
	"fmt"
	"os/exec"
	"strings"
	"time"
)

func runReconcileStats(ctx context.Context, settings Settings) error {
	store, err := OpenStatsStore(settings.StatsDBPath)
	if err != nil {
		return err
	}
	defer store.Close()
	state, err := store.ReconciliationState(ctx)
	if err != nil {
		return err
	}
	if err := reconcileJournalctl(ctx, store, state.JournalCursor); err != nil {
		if state.JournalCursor == "" || !strings.Contains(strings.ToLower(err.Error()), "cursor") {
			return err
		}
		return reconcileJournalctl(ctx, store, "")
	}
	return nil
}

func reconcileJournalctl(ctx context.Context, store *StatsStore, cursor string) error {
	args := []string{
		"--output=json", "--no-pager",
		"--unit=testcase-ac-backend-blue.service",
		"--unit=testcase-ac-backend-green.service",
	}
	if cursor != "" {
		args = append(args, "--after-cursor="+cursor)
	}
	cmd := exec.CommandContext(ctx, "journalctl", args...)
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		return err
	}
	var stderr bytes.Buffer
	cmd.Stderr = &stderr
	if err := cmd.Start(); err != nil {
		return err
	}
	if err := store.reconcileJournal(ctx, stdout, time.Now().UTC(), cmd.Wait); err != nil {
		if stderr.Len() > 0 {
			return fmt.Errorf("journalctl: %s: %w", strings.TrimSpace(stderr.String()), err)
		}
		return err
	}
	return nil
}
