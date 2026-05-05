import random
ranset = random.randint

Type = ranset(1, 3)
N = 0
if Type <= 2 :
  N = ranset(1, 5)
  print(N)
  for i in range(N) :
    print(ranset(0, 30), end=" ")
else :
  N = ranset(1, 100000)
  print(N)
  for i in range(N) :
    print(ranset(0, 10000), end=" ")
