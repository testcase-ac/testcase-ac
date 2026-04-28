n = int(input())
ans = 0

for i in range(1, n + 1):
  ans += 1
  if '50' in str(i): ans += 1

if '50' in str(n): ans -= 1
print(ans)
