import sys
r = sys.stdin.readline

def solve():
  n = int(r())
  a = list(map(int, r().split()))

  if n == 1:
    return a[0] == 2

  if a[-1] == 1:
    lb, avail = 2, 3
  elif a[-1] == 2:
    lb, avail = 2, 4
  else:
    return False

  for x in range(n - 1):
    i = n - 2 - x
    if a[i] < lb or a[i] > avail: return False

    lb = a[i]
    if i > 0: avail = (avail - a[i]) + 2 * a[i]
    elif avail != a[i]: return False

  return True

t = int(r())
for _ in range(t): print('YES' if solve() else 'NO')
