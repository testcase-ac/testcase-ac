import random
ranset = random.randint

Type = ranset(1, 3)
if Type <= 2 :
  print(ranset(1, 10), ranset(1, 10))
else :
  print(ranset(1, 1000), ranset(1, 1000))
