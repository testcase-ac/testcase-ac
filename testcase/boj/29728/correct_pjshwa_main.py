n = int(input())

lp = [0] * (n + 1)
primes = []
for i in range(2, n + 1):
  if lp[i] == 0:
    lp[i] = i
    primes.append(i)

  for pr in primes:
    if pr > lp[i] or i * pr > n: break
    lp[i * pr] = pr

def is_prime(n):
  return lp[n] == n

if n == 1: print("1 0")
elif n == 2: print("0 2")
elif n == 3: print("0 3")
else:
  b, s = 0, 3
  for i in range(4, n + 1):
    if is_prime(i):
      b -= 1
      s += 2
    else:
      b += 1
  print(f"{b} {s}")
