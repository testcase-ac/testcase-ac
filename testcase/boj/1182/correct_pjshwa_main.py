import sys
n, s = map(int, sys.stdin.readline().split())
numbers = list(map(int, sys.stdin.readline().split()))

sum_counter = 0
import itertools
for i in range(1, n+1):
	for item in itertools.combinations(numbers, i):
		if sum(item) == s:
			sum_counter += 1

print(sum_counter)