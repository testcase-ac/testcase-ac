primes_list = [True] * 100001

import sys
r = sys.stdin.readline

primes_list[0] = False
primes_list[1] = False

for i in range(int(100000**0.5)):
	if primes_list[i]:
		idx = 2
		while i * idx <= 100000:
			primes_list[i*idx] = False
			idx += 1

n = int(r())
for _ in range(n):
	num = int(r())
	for i in range(100001):
		if primes_list[i]:
			it = 0
			while num % i == 0:
				num //= i
				it += 1
			if it: print(i, it)
		if num == 1: break