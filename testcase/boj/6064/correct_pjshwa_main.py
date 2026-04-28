import sys
r = sys.stdin.readline
t = int(r())

for _ in range(t):
    m, n, x, y = map(int, r().split())
    if abs(y - x) % abs(n - m) != 0 and abs(n - m) % abs(y - x) != 0:
        print(-1)
        continue
    while x % n != y:
        x += m
    print(x)
