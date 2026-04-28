t = int(input())

def is_prime(n):
  if n == 2: return True
  if n % 2 == 0: return False
  for i in range(3, int(n**0.5)+1, 2):
    if n % i == 0: return False
  return True

def solve(n):
  for i in range(2, n//2+1):
    if is_prime(i) and is_prime(n-i):
      return 'Yes'
  return 'No'

for _ in range(t):
  n = int(input())
  print(solve(n))
