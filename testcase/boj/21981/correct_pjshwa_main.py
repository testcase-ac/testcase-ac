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

def parse_time(tstr):
  t = list(map(int, tstr.split(':')))
  return t[0] * 3600 + t[1] * 60 + t[2]

IV = (24 * 3600)
t = int(r())
for _ in range(t):
  n = int(r())
  T = list(map(parse_time, r().split()))
  D = list(map(int, r().split()))

  able = True
  nums = []
  mods = []
  for i in range(n - 1):
    tdiff = (T[i + 1] - T[i] + IV) % IV
    ddiff = D[i + 1] - D[i]
    if ddiff < 0:
      tdiff = IV - tdiff
      ddiff = -ddiff

    g = math.gcd(tdiff, math.gcd(ddiff, IV))
    tdiff //= g
    ddiff //= g
    iv = IV // g

    if ddiff == 0 and tdiff != 0:
      able = False
      break

    mi = extended_euclidean(ddiff, iv)[1]
    if mi < 0: mi += iv
    nums.append((tdiff * mi) % iv)
    mods.append(iv)

  if able:
    num, mod = crt(nums, mods)
    if num < 0: print(0)
    else:
      ans = 0
      while num < IV:
        ans += 1
        num = num + mod
      print(ans)
  else: print(0)
