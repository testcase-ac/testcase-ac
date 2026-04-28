def square(n):
  return n * n

def P3(x, y, z):
  if x == 100: return (square(100 - y) + square(100 - z)) ** 0.5
  if y == 100: return (square(100 - x) + square(100 - z)) ** 0.5
  if z == 100: return (square(100 - x) + square(100 - y)) ** 0.5
  if x == 0: return min(square(200 - z) + square(100 - y), square(100 - z) + square(200 - y)) ** 0.5
  if y == 0: return min(square(200 - x) + square(100 - z), square(100 - x) + square(200 - z)) ** 0.5
  if z == 0: return min(square(200 - y) + square(100 - x), square(100 - y) + square(200 - x)) ** 0.5
