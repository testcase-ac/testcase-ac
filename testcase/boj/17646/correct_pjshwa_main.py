import random
from math import gcd

def ipow(x, y, p):
  ret = 1
  while y > 0:
    if (y&1) == 1:
      ret = ret*x%p
    x = x*x%p
    y >>= 1
  return ret

def is_prime(x):

  def miller_rabin(x, a):
    if x%a == 0:
      return False
    d = x-1
    while True:
      k = ipow(a, d, x)
      if (d&1) == 1:
        return (k != 1 and k != x-1)
      elif k == x-1:
        return False
      d >>= 1

  for i in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]:
    if x == i:
      return True
    if x > 40 and miller_rabin(x, i):
      return False
  
  return x > 40

def factorize(n):

  def rec(n, ret):
    if n == 1:
      return
    if n%2 == 0:
      ret.append(2)
      rec(n//2, ret)
      return
    if is_prime(n):
      ret.append(n)
      return
    
    while True:
      a = random.randint(2, n-1)
      b = a
      c = random.randint(1, 20)
      
      do_while_flag = True      
      while do_while_flag or gcd(abs(a-b), n) == 1:
        do_while_flag = False
        def f(x):
          return (c+x*x)%n
        a = f(a)
        b = f(f(b))
      
      if a != b: break
    
    x = gcd(abs(a-b), n)
    rec(x, ret)
    rec(n//x, ret)
    return

  ret = []
  rec(n, ret)
  return sorted(ret)
  
class GaussianInteger:
  
  def __init__(self, re, im):
    self.re = re
    self.im = im
  
  def norm(self):
    return self.re*self.re+self.im*self.im
    
  
  def __floordiv__(w, z):
  
    def rem(a, b):
      ret = a%b
      if ret < 0: ret += b
      if 2*ret > b: ret -= b
      return ret
    
    def quo(a, b):
      return (a-rem(a,b))//b
  
    w0, w1 = w.re, w.im
    z0, z1 = z.re, z.im
    N = z.norm()
    u0, u1 = quo(w0*z0+w1*z1, N), quo(w1*z0-w0*z1, N)
    return GaussianInteger(u0, u1)
  
  def __mod__(a, b):
    a0, a1 = a.re, a.im
    b0, b1 = b.re, b.im
    q = a//b
    q0, q1 = q.re, q.im
    r0 = a0-q0*b0+q1*b1
    r1 = a1-q0*b1-q1*b0
    return GaussianInteger(r0, r1)
    
  @staticmethod
  def gcd(w, z):
    while z.re != 0 or z.im != 0:
      w, z = z, w%z
    
    return w
  
def quadratic_residue(p):
  k = p//4
  j = 2
  while True:
    a = ipow(j, k, p)
    b = a*a%p
    if b == p-1: return a
    j += 1

def sum_of_two_squares_prime(p):
  if p == 2: return (1, 1)
  a = quadratic_residue(p)
  g = GaussianInteger.gcd(GaussianInteger(p, 0), GaussianInteger(a, 1))
  return (abs(g.re), abs(g.im))

def sum_of_two_squares(N):
  square = 1
  primes = set()
  for x in factorize(N):
    if x in primes:
      square *= x
      primes.remove(x)
    else:
      primes.add(x)
  
  if len(primes) == 0:
    return (square, 0)
  
  for x in primes:
    if x%4 == 3:
      return None
  
  a, b = square, 0
  for x in primes:
    c, d = sum_of_two_squares_prime(x)
    a, b = a*c+b*d, a*d-b*c
  
  return (abs(a), abs(b))

def sum_of_squares(n):
  if n == 0: return []

  cnt = 0
  if n%4 == 0:
    while n%4 == 0:
      n //= 4
      cnt += 1

    return list(map(lambda x: x<<cnt, sum_of_squares(n)))
  
  if n%8 == 7:
    return sum_of_squares(n-1) + [1]
  
  ab = sum_of_two_squares(n)
  if ab is not None:
    a, b = ab
    ret = []
    if a != 0: ret.append(a)
    if b != 0: ret.append(b)
    return ret
  
  i = 2
  if n%4 == 3: i = 1
  
  while True:
    ab = sum_of_two_squares(n-i*i)
    if ab is not None:
      return list(ab) + [i]
  
    i += 2
  
def main():
  N = int(input())
  sos = sum_of_squares(N)
  print(len(sos))
  print(" ".join(map(str, sos)))


if __name__ == '__main__':
  main()
