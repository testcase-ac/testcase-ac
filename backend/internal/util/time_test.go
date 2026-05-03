package util

import (
	"testing"
	"time"
)

func TestRoundSeconds(t *testing.T) {
	tests := []struct {
		name string
		in   time.Duration
		want float64
	}{
		{name: "whole milliseconds", in: 2345 * time.Millisecond, want: 2.345},
		{name: "truncates sub-millisecond", in: 2345*time.Millisecond + 999*time.Microsecond, want: 2.345},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := RoundSeconds(tt.in); got != tt.want {
				t.Fatalf("RoundSeconds(%v) = %v, want %v", tt.in, got, tt.want)
			}
		})
	}
}
