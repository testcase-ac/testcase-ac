import sys
r = sys.stdin.readline

n, m, k = map(int, r().split())
print('{} {}'.format(k // m, k % m))