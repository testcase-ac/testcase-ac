import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

Type = ranset(1, 4)
if Type == 1 :
  N = ranset(1, 5)
  print(N)
  for i in range(N) :
    print(ranset(0, 4), end="\n" if i == N - 1 else " ")
elif Type == 2 :
  N = ranset(1, 5)
  print(N)
  for i in range(N) :
    print(ranset(0, 16), end="\n" if i == N - 1 else " ")
elif Type == 3 :
  N = ranset(1, 45)
  print(N)
  for i in range(N) :
    print(ranset(0, 1000), end="\n" if i == N - 1 else " ")
else :
  N = ranset(46, 50)
  print(N)
  for i in range(N) :
    print(ranset(0, 1000), end="\n" if i == N - 1 else " ")
