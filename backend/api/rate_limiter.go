package main

import (
	"sync"
	"time"
)

type RateLimiter struct {
	maxRequests  int
	window       time.Duration
	mu           sync.Mutex
	bucketsByKey map[string][]time.Time
}

func NewRateLimiter(maxRequests int, windowSeconds float64) *RateLimiter {
	return &RateLimiter{
		maxRequests:  maxRequests,
		window:       time.Duration(windowSeconds * float64(time.Second)),
		bucketsByKey: make(map[string][]time.Time),
	}
}

func (r *RateLimiter) Check(key string) bool {
	now := time.Now()
	cutoff := now.Add(-r.window)

	r.mu.Lock()
	defer r.mu.Unlock()

	bucket := r.bucketsByKey[key]
	kept := bucket[:0]
	for _, ts := range bucket {
		if ts.After(cutoff) {
			kept = append(kept, ts)
		}
	}
	if len(kept) >= r.maxRequests {
		r.bucketsByKey[key] = kept
		return false
	}
	kept = append(kept, now)
	r.bucketsByKey[key] = kept
	return true
}
