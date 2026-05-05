import random
ranset = random.randint

Type = ranset(1, 3)
N, K, X = 0, 0, 0
if Type <= 2 :
  N, X = ranset(1, 5), ranset(1, 10)
  K = ranset(1, N)
else :
  N, X = ranset(1, 80), ranset(1, 200)
  K = ranset(1, N)
print(N, K, X)
for i in range(N) :
  dif = ranset(0, X)
  print(dif, X-dif)
