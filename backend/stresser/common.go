package main

import (
	"encoding/json"
	"fmt"
	"log/slog"
	"os"
	"path/filepath"
	"strconv"
	"strings"
	"syscall"
	"unicode/utf8"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

const diskCleanupThresholdPercent = 60.0

type ResponseError struct {
	errorType contracts.ErrorType
	details   map[string]any
}

func NewResponseError(errorType contracts.ErrorType, details map[string]any) *ResponseError {
	if details == nil {
		details = map[string]any{}
	}
	return &ResponseError{errorType: errorType, details: details}
}

func (e *ResponseError) Error() string {
	payload, _ := json.Marshal(e.details)
	return fmt.Sprintf("%s: %s", e.errorType, string(payload))
}

func (e *ResponseError) ToResponse(requestID string) contracts.StressResult {
	return contracts.StressResult{
		RequestID: requestID,
		Error:     true,
		ErrorType: e.errorType,
		Message:   truncateTestcase(mustJSON(e.details), 4000, 40),
	}
}

func intInFirstLine(s string) []int {
	if s == "" {
		return nil
	}
	if newline := strings.IndexByte(s, '\n'); newline >= 0 {
		s = s[:newline]
	}
	out := []int{}
	for _, field := range strings.Fields(s) {
		if n, err := strconv.Atoi(field); err == nil {
			out = append(out, n)
		}
	}
	return out
}

func truncateTestcase(testcase string, maxLength int, maxLine int) string {
	lines := strings.Split(testcase, "\n")
	lineTruncated := len(lines) > maxLine
	truncatedByLines := testcase
	if lineTruncated {
		truncatedByLines = strings.Join(lines[:maxLine], "\n")
	}
	charTruncated := utf8.RuneCountInString(truncatedByLines) > maxLength
	finalResult := truncatedByLines
	if charTruncated {
		finalResult = firstNRunes(truncatedByLines, maxLength)
	}
	if lineTruncated || charTruncated {
		testcaseLen := utf8.RuneCountInString(strings.TrimSuffix(testcase, "\n"))
		lineLen := len(lines)
		if strings.HasSuffix(testcase, "\n") && lineLen > 0 {
			lineLen--
		}
		return fmt.Sprintf("%s(...truncated, total %d characters, %d lines)", finalResult, testcaseLen, lineLen)
	}
	return testcase
}

func textWithMetadata(s string, maxLength int, maxLine int) contracts.TextWithMetadata {
	totalLength := utf8.RuneCountInString(s)
	totalLines := countOutputLines(s)
	metadata := contracts.OutputTextMetadata{
		CharacterCount: totalLength,
		LineCount:      totalLines,
	}

	lines := strings.Split(s, "\n")
	lineCut := -1
	if totalLines > maxLine {
		lineCut = utf8.RuneCountInString(strings.Join(lines[:maxLine], "\n"))
	}

	charCut := -1
	if totalLength > maxLength {
		charCut = maxLength
	}
	if lineCut < 0 && charCut < 0 {
		return contracts.TextWithMetadata{Text: s, Metadata: metadata}
	}

	truncatedAt := minPositive(lineCut, charCut)
	truncatedBy := contracts.TruncationKindCharacter
	truncatedAtLine := (*int)(nil)
	if lineCut >= 0 && lineCut <= truncatedAt {
		truncatedBy = contracts.TruncationKindLine
		truncatedAtLine = intPtr(maxLine)
	}
	metadata.Truncated = true
	metadata.TruncatedBy = truncationKindPtr(truncatedBy)
	metadata.TruncatedAtCharacter = intPtr(truncatedAt)
	metadata.TruncatedAtLine = truncatedAtLine

	return contracts.TextWithMetadata{
		Text:     firstNRunes(s, truncatedAt),
		Metadata: metadata,
	}
}

func countOutputLines(s string) int {
	if s == "" {
		return 0
	}
	lineCount := len(strings.Split(s, "\n"))
	if strings.HasSuffix(s, "\n") {
		lineCount--
	}
	return lineCount
}

func truncationKindPtr(value contracts.TruncationKind) *contracts.TruncationKind {
	return &value
}

func checkAndCleanTmp() error {
	var stat syscall.Statfs_t
	if err := syscall.Statfs("/tmp", &stat); err != nil {
		return err
	}
	total := float64(stat.Blocks) * float64(stat.Bsize)
	available := float64(stat.Bavail) * float64(stat.Bsize)
	used := total - available
	usagePercent := (used / total) * 100
	if usagePercent <= diskCleanupThresholdPercent {
		slog.Info("tmp_disk_usage", "usage_percent", usagePercent)
		return nil
	}

	slog.Warn("tmp_disk_cleanup_start", "usage_percent", usagePercent, "threshold_percent", diskCleanupThresholdPercent)
	entries, err := os.ReadDir("/tmp")
	if err != nil {
		return err
	}
	for _, entry := range entries {
		path := filepath.Join("/tmp", entry.Name())
		if err := os.RemoveAll(path); err != nil {
			slog.Warn("tmp_remove_failed", "path", path, "err", err)
		}
	}
	var after syscall.Statfs_t
	if err := syscall.Statfs("/tmp", &after); err == nil {
		usedAfter := (float64(after.Blocks) - float64(after.Bavail)) * float64(after.Bsize)
		freedMB := (used - usedAfter) / (1024 * 1024)
		slog.Info("tmp_disk_cleanup_done", "freed_mb", freedMB)
	}
	return nil
}

func logTmpUsage() {
	var stat syscall.Statfs_t
	if err := syscall.Statfs("/tmp", &stat); err != nil {
		slog.Warn("tmp_disk_usage_failed", "err", err)
		return
	}
	total := float64(stat.Blocks) * float64(stat.Bsize)
	available := float64(stat.Bavail) * float64(stat.Bsize)
	used := total - available
	usagePercent := (used / total) * 100
	slog.Info("tmp_disk_usage", "usage_percent", usagePercent)
}

func mustJSON(value any) string {
	data, err := json.Marshal(value)
	if err != nil {
		return "{}"
	}
	return string(data)
}

func intPtr(value int) *int {
	return &value
}

func stringPtr(value string) *string {
	return &value
}

func minPositive(values ...int) int {
	best := -1
	for _, value := range values {
		if value < 0 {
			continue
		}
		if best < 0 || value < best {
			best = value
		}
	}
	return best
}

func firstNRunes(s string, n int) string {
	if n <= 0 {
		return ""
	}
	runeCount := 0
	for i := range s {
		if runeCount == n {
			return s[:i]
		}
		runeCount++
	}
	return s
}
