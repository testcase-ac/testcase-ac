import math

def P1(x1,y1,x2,y2,x3,y3):
  return math.gcd(x2 - x1, y2 - y1) + math.gcd(x3 - x1, y3 - y1) + math.gcd(x3 - x2, y3 - y2)
