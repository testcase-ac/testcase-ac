import sys
r = sys.stdin.readline

n, k = map(int, r().split())

minv, maxv = 0, 0
ranges = []
for _ in range(n):
  a, b = map(int, r().split())
  a = max(a, 1)
  minv += a; maxv += b
  ranges.append([a, b])

if maxv < k or minv > k: print('FAIL')
else:
  chunks = [ranges[i][0] for i in range(n)]
  current_sum = sum(chunks)

  for i in range(n):
    if current_sum < k:
      dif = k - current_sum
      addend = min(ranges[i][1] - ranges[i][0], dif)
      chunks[i] += addend
      current_sum += addend

  assert sum(chunks) == k

  output = ['SUCCESS']; left = 1
  for chunk in chunks:
    output.append(f"{left} {left + chunk - 1}")
    left += chunk

  print("\n".join(output))
