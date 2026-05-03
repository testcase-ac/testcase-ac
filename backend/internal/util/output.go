package util

import "strings"

// CleanStdout normalizes one stdout/testcase stream before feeding it onward.
func CleanStdout(output string, trailingNewline string) string {
	trimmed := strings.TrimRight(output, "\n\r\t ")
	if trimmed == "" {
		if trailingNewline == "always" {
			return "\n"
		}
		return ""
	}
	lines := strings.Split(trimmed, "\n")
	for i, line := range lines {
		lines[i] = strings.TrimRight(line, " \t\r")
	}
	cleaned := strings.Join(lines, "\n")
	if trailingNewline == "always" {
		return cleaned + "\n"
	}
	return cleaned
}

// CompareOutput applies BOJ-style no-checker judging.
// - "space" and "newline" are treated equally
// - "newline" and "space + newline" are treated equally
// - but "space" and "space + newline" are NOT treated equally.
func CompareOutput(a, b string) bool {
	a = strings.TrimRight(a, "\n\r\t ")
	b = strings.TrimRight(b, "\n\r\t ")
	if strings.ReplaceAll(a, "\n", " ") == strings.ReplaceAll(b, "\n", " ") {
		return true
	}
	return strings.ReplaceAll(a, " \n", "\n") == strings.ReplaceAll(b, " \n", "\n")
}
