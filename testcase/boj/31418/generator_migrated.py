import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

Type = ranset(1, 6)
if Type <= 5 :
  W, H, K, T = ranset(1, 5), ranset(1, 5), ranset(1, 5), ranset(0, 4)
  print(W, H, K, T)
  for i in range(K) :
    print(ranset(1, W), ranset(1, H))
else :
  W, H, K, T = ranset(1, 10**6), ranset(1, 10**6), ranset(1, 10**5), ranset(0, 10**6)
  print(W, H, K, T)
  for i in range(K) :
    print(ranset(1, W), ranset(1, H))
