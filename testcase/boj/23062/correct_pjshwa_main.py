import math, sys
r = sys.stdin.readline

def extended_euclidean(a, b):
  if b == 0: return [a, 1, 0]
  g, x, y = extended_euclidean(b, a % b)
  return [g, y, x - (a // b) * y]

def crt(nums, mods):
  num = nums[0]
  mod = mods[0]
  for (a, m) in list(zip(nums, mods))[1:]:
    g = math.gcd(mod, m)
    if not num % g == a % g: return (-1, -1)
    _, p, q = extended_euclidean(mod // g, m // g)

    new_mod = mod * m // g
    num = (num * (m // g) * q + a * (mod // g) * p) % new_mod
    mod = new_mod
    if num < 0: num += mod
  return (num, mod)

t = int(r())
for _ in range(t):
  a, b, c, d, e, f = map(int, r().split())
  print(crt([d, e, f], [a, b, c])[0])
