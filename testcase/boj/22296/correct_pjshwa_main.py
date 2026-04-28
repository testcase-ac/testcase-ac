from functools import reduce
from itertools import product
from math import gcd

def factors(n):
  return set(reduce(list.__add__,
          ([i, n//i] for i in range(1, int(n**0.5) + 1) if n % i == 0)))

def is_rational_root(a, b, c, d, p1, p2):
  return a * p1 * p1 * p1 + b * p1 * p1 * p2 + c * p1 * p2 * p2 + d * p2 * p2 * p2 == 0

def solve_linear(c, d):
  return set() if c == 0 else {(-d / c)}

def solve_quadratic(b, c, d):
  if b == 0: return solve_linear(c, d)
  if d == 0: return solve_linear(b, c) | {0}

  fd = factors(abs(d))
  fb = factors(abs(b))
  answers = set()
  for p1 in fd:
    for p2 in fb:
      if gcd(p1, p2) == 1:
        if is_rational_root(0, b, c, d, p1, p2): answers.add(p1 / p2)
        if is_rational_root(0, b, c, d, -p1, p2): answers.add(-p1 / p2)

  return answers

def solve_cubic(a, b, c, d):
  if a == 0: return solve_quadratic(b, c, d)
  if d == 0: return solve_quadratic(a, b, c) | {0}

  fd = factors(abs(d))
  fa = factors(abs(a))
  answers = set()
  for p1 in fd:
    for p2 in fa:
      if gcd(p1, p2) == 1:
        if is_rational_root(a, b, c, d, p1, p2): answers.add(p1 / p2)
        if is_rational_root(a, b, c, d, -p1, p2): answers.add(-p1 / p2)

  return answers

P7 = lambda *p: list(solve_cubic(*p))

############### SUBMIT THE CODE ABOVE ONLY ###############

print(P7(4,-2,-4,2)) # [-1.0, 0.5, 1.0]
print(P7(3,2,1,0)) # [0.0]
print(P7(0,1,-4,4)) # [2.0]
print(P7(1,2,1,0)) # [0.0]
print(P7(3,-4,-17,6)) # [0.3333333333333333, 3.0, -2.0]
print(P7(0,0,5,8)) # [-1.6]
print(P7(1,-4,4,0)) # [0.0, 2.0]
print(P7(735134400,1234,1234,735134400))
