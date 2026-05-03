package util

import "time"

func RoundSeconds(d time.Duration) float64 {
	return float64(d.Milliseconds()) / 1000.0
}
