import random
ranset = random.randint

Type = ranset(1, 10)
T, N, D, K = 0, 0, 0, 0
if Type <= 5 :
  T, N, D, K = ranset(10, 100), ranset(1, 10), ranset(1, 5), ranset(1, 5)
elif Type <= 9:
  T, N, D, K = ranset(20, 150), ranset(1, 20), ranset(1, 100), ranset(1, 10)
else :
  T, N, D, K = ranset(1, 10**9), ranset(1, 10**6), ranset(1, 10**9), ranset(1, 10)
print(T, N, D, K)
for i in range(N) :
  print(ranset(1, T), end=" ")
