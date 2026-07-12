import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint
ransam = random.sample

Type = ranset(1, 10)

if Type <= 7 :
  N = ranset(3, 8)
  S = ranset(-3, 3)
  print(N, S)
  for i in range(N) :
    print(ranset(-3, 3), end="\n" if i + 1 == N else " ")
elif Type <= 9 :
  N = ranset(1, 40)
  S = ranset(-10, 10)
  print(N, S)
  for i in range(N) :
    print(ranset(-10, 10), end="\n" if i + 1 == N else " ")
else :
  N = ranset(1, 40)
  S = ranset(-1000000, 1000000)
  print(N, S)
  for i in range(N) :
    print(ranset(-100000, 100000), end="\n" if i + 1 == N else " ")
