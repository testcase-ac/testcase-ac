from decimal import *
import math
getcontext().prec = 4000

def solve(n):
  x0, x1 = Decimal(0), Decimal(1)
  xn = Decimal(0)
  for i in range(2, n + 1):
    xn = (x0 + x1) / Decimal(2)
    x0, x1 = x1, xn

  str_xn, ret = str(xn), 0
  for i in range(len(str_xn)):
    if i == 0 or i == 1: continue
    if str_xn[i] == '6': ret += 1
    else: break
  return ret

n = int(input())
for i in range(1, n + 1):
  print(f"Case #{i}: {solve(i)}")
