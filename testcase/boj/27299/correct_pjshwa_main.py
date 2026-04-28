import sys, functools
r = sys.stdin.readline

@functools.lru_cache(maxsize=None)
def phi(n):
  if n < 3: return 1

  phi = n
  prime = 2

  while prime ** 2 <= n:
    if n % prime == 0: phi = phi // prime * (prime - 1)
    while n % prime == 0: n //= prime
    prime += 1

  if not n == 1: phi = phi // n * (n - 1)
  return phi

def solve():
  a, b, i, c = map(int, r().split())
  m = int(1e7)

  if b <= 4 and c <= 10:
    pw = 1
    for _ in range(c): pw *= b
    u = pow(a, pw, m)
  else:
    o = pow(b, c, phi(m))
    u = pow(a, o + phi(m), m)

  s = list(reversed(str(u)))
  print(s[i] if i < len(s) else 0)

t = int(r())
for _ in range(t): solve()
