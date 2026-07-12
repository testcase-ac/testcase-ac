import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

Type = ranset(1, 5)
if Type <= 4 :
  N = ranset(1, 5)
  print(N)
  for i in range(N) :
    print(ranset(1, 10), end="\n" if i == N - 1 else " ")
  for i in range(N) :
    print(ranset(1, 10), end="\n" if i == N - 1 else " ")
else :
  N = ranset(1, 50)
  print(N)
  for i in range(N) :
    print(ranset(1, 1000), end="\n" if i == N - 1 else " ")
  for i in range(N) :
    print(ranset(1, 1000), end="\n" if i == N - 1 else " ")
  
