import sys

s, k = map(int, sys.stdin.readline().split())

n = s // k
p = s % k
print(((n + 1) ** p) * (n ** (k - p)))