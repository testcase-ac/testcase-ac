import sys
r = sys.stdin.readline

def pad(n, h):
    result = n % h
    if result == 0: return (h, n//h)
    else: return (result, n//h+1)

t = int(r())
for _ in range(t):
    h, w, n = map(int, r().split())
    print("{}{:02d}".format(*pad(n,h)))