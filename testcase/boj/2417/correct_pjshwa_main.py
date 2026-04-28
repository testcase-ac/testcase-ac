import math

n = int(input())
s_n = math.sqrt(n)
for it in range(5):
  q = int(s_n) - 2 + it
  if q < 0: continue
  if q * q >= n:
    print(q)
    break
