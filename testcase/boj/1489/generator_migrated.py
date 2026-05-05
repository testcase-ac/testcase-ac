import random
ranset = random.randint

Type = ranset(1, 5)
if Type <= 4 :
  N = ranset(1, 5)
  print(N)
  for i in range(N) :
    print(ranset(1, 10), end=" ")
  print()
  for i in range(N) :
    print(ranset(1, 10), end=" ")
else :
  N = ranset(1, 50)
  print(N)
  for i in range(N) :
    print(ranset(1, 1000), end=" ")
  print()
  for i in range(N) :
    print(ranset(1, 1000), end=" ")
  
