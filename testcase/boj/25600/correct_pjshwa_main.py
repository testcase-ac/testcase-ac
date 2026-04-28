import sys
r = sys.stdin.readline

n = int(r())
ans = 0
for i in range(n):
  a, d, g = map(int, r().split())
  score = a * (d + g)
  if a == d + g: score *= 2
  ans = max(ans, score)

print(ans)
