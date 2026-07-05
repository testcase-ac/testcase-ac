import sys
from math import gcd

r = sys.stdin.readline
t = int(r())

for _ in range(t):
    m, n, x, y = map(int, r().split())
    if (y - x) % gcd(m, n) != 0:
        print(-1)
        continue
    while x % n != y % n:
        x += m
    print(x)
