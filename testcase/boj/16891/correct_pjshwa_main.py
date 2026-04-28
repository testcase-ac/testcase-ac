import math

def P6(n):
  if n == 1: return 3
  return int(math.pi / math.atan(1 / (n ** 0.5)))

n = int(input())
print(P6(n * n))
