Ps, pw = [0, 2], 100
for i in range(3, 56):
  # cube root of pw
  j = int(round(pw ** (1.0 / 3))) - 2
  while True:
    u, d = j ** 3, 0
    while u:
      d += 1
      u //= 10
    if d == i:
      break
    j += 1
  Ps.append(j - 1)
  pw *= 10

# How many digits if we count to d?
def f(d):
  s = 0
  for j in range(1, 55):
    s += j * (min(m, Ps[j]) - Ps[j - 1])
    if Ps[j] > m: break
  return s

l, r, k = 1, int(1e18), int(input())
while l < r:
  m = (l + r) // 2
  s = f(m)
  if s >= k:
    r = m
  else:
    l = m + 1

k -= f(l - 1)
print(str(l * l * l)[k - 1])
