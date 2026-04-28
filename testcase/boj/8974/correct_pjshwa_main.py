import sys
a, b = map(int, sys.stdin.readline().split())

def sum_to_idx(i):
	root = int((i*2) ** 0.5)
	if i >= root * (root + 1) // 2: idx = root
	else: idx = root - 1

	next_sum = (idx + 1) * (i - idx * (idx + 1) // 2)
	prev_sum = (idx + 1) * idx * (2 * idx + 1) // 6

	return next_sum + prev_sum

print(sum_to_idx(b) - sum_to_idx(a-1))