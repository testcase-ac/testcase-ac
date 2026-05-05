import random
ranset = random.randint
Type = ranset(1, 30)
if Type <= 27 :
  N, L = ranset(3, 7), ranset(0, 10)
  stanG = ranset(L, L+5)
  G, S, B = stanG-L, ranset(1, 20), ranset(1, 20)
  print(N, L)
  print(G, S, B)
  for i in range(1, N, 1) :
    print(stanG, ranset(1, 20), ranset(1, 20))
elif Type <= 29 :
  N, L = ranset(3, 7), ranset(0, 10)
  print(N, L)
  for i in range(N) :
    print(ranset(0, 10), ranset(0, 20), ranset(0, 20))
else :
  N, L = ranset(3, 50), ranset(0, 10000) 
  print(N, L)
  for i in range(N) :
    print(ranset(0, 10000), ranset(0, 10000), ranset(0, 10000))
