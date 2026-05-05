import random
ranset = random.randint
ransam = random.sample

Type = ranset(1, 14)
N, M = 0, 0
P = [0]*(10)

if Type <= 6 :
  N = ranset(1, 5)
  M = ranset(20, 50)
  for i in range(N) :
    P[i] = ranset(1, 2*M)
elif Type <= 12 :
  N = ranset(1, 5)
  M = ranset(20, 50)
  stan = ranset(2, M//4)
  for i in range(N) :
    P[i] = ranset(stan-1, stan+1)
elif Type <= 13 :
  N = ranset(1, 10)
  M = ranset(0, 10*18)
  for i in range(N) :
    P[i] = ranset(1, 10)
else :
  N = ranset(1, 10)
  M = ranset(0, 10*18)
  for i in range(N) :
    P[i] = ranset(1, 10**18)

print(N)
for i in range(N) :
  print(P[i], end=" ")
print()
print(M)
