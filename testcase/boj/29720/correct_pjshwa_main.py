import sys
r = sys.stdin.readline

n, m, k = map(int, r().split())
mmin = max(0, n - m * k)
mmax = n - m * k + m - 1
print(mmin, mmax)
