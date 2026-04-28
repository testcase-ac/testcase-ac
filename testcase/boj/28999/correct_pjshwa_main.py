import sys
r = sys.stdin.readline

n, q = map(int, r().split())
a = list(map(int, r().split()))

delta = [0 for _ in range(n + 1)]
for _ in range(q):
  left, right = map(int, r().split())
  delta[left - 1] += 1; delta[right] -= 1

weights = [0 for _ in range(n + 1)]
for i in range(n):
  if i: weights[i] = weights[i - 1] + delta[i]
  else: weights[i] = delta[i]

ans = 0
a.sort(reverse=True)
weights.sort(reverse=True)
for i in range(n): ans += a[i] * weights[i]

print(ans)
