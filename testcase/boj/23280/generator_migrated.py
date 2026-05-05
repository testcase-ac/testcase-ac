import random
ranset = random.randint
N = 0
Type = ranset(1, 4)
if Type <= 2 :
  N = ranset(1, 10)
  print(N, ranset(1, 8), ranset(1, 8))
elif Type == 3 :
  N = ranset(11, 9900)
  print(N, ranset(1, 100), ranset(1, 100))
else :
  N = ranset(9901, 10000)
  print(N, ranset(1, 100), ranset(1, 100))
for i in range(N) :
  print(ranset(1, 12), end=" ")
