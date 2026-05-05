import random
ranset = random.randint

Type = ranset(0, 27)
N, M, K = 0, 0, 0

if Type%7 <= 4 :
  N, M = ranset(1, 5), ranset(1, 5)
  if N == 1 or M == 1 :
    K = ranset(1, min(4, (N*M+1)//2))
  else :
    K = ranset(1, min(4, N*M//2))
else :
  N, M = ranset(3, 10), ranset(3, 10)
  K = ranset(1, min(4, N*M))
print(N, M, K)

if Type/7 <= 2 :
  for i in range(N) :
    for j in range(M) :
      print(ranset(-5, 5), end=' ')
    print()
else :
  for i in range(N) :
    for j in range(M) :
      print(ranset(-10000, 10000), end=' ')
    print()
