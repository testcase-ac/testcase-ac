primes = []
MAX = 100_000
sieve = [True for _ in range(MAX + 1)]
sieve[0] = sieve[1] = False
for i in range(2, MAX + 1):
  if sieve[i]: primes.append(i)
  for j in primes:
    if i * j > MAX: break
    sieve[i * j] = False

def isPrime(n):
  return sieve[n]

def isSquare(n):
  if n < 0: return False
  sqrt = round(n ** 0.5)
  return sqrt ** 2 == n

def P2(A):
  s = 0
  for i, e in enumerate(A):
    if isPrime(i) and isSquare(e): s += e
  return s

############### SUBMIT THE CODE ABOVE ONLY ###############

print(P2([0, 100, 20, 100, 40])) # 100
print(P2([1])) # 100
print(P2([50, 50])) # 100
print(P2([0, 100, -20, 100, 40] * 20000)) # 100
