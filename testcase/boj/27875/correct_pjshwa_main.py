# https://literateprograms.org/pi_with_the_bbp_formula__python_.html

def S(j, n):
  # Left sum
  s = 0.0
  k = 0
  while k <= n:
    r = (8*k+j)**2
    s = (s + float(pow(16, n-k, r)) / r) % 1.0
    k += 1

  # Right sum
  t = 0.0
  k = n + 1
  while 1:
    newt = t + pow(16, n-k) / ((8*k+j)**2)
    # Iterate until t no longer changes
    if t == newt:
        break
    else:
        t = newt
    k += 1

  return s + t

def pi(n):
  n -= 1
  x = (16*S(1, n) - 16*S(2, n) - 8*S(3, n) - 16*S(4, n) - 4*S(5, n) - 4*S(6, n) + 2*S(7, n)) % 1.0
  return "%0X" % int(x * 16)

print(pi(int(input())))
