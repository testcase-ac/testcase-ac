import math

def P6(n):
  if n == 1: return 3
  return int(math.pi / math.atan(1 / (n ** 0.5)))

# print(P6(1))
# print(P6(2))
# print(P6(3))
# print(P6(4))
# print(P6(5))
# print(P6(6))
# print(P6(7))
# print(P6(8))
# print(P6(9))
# print(P6(10))
# print(P6(16))
# print(P6(64))
# print(P6(100))
# print(P6(10000))
# print(P6(1000000))
