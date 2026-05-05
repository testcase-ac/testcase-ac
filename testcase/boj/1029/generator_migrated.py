import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint
ransam = random.sample

Type = ranset(1, 5)

if Type <= 4 :
  N = 0
  if Type <= 2:
    N = ranset(2, 3)
  else :
    N = 4
  print(N)
  for i in range(N) :
    for j in range(N) :
      print(ranset(0, 4), end='')
    print()
else :
  N = ranset(2, 15)
  print(N)
  for i in range(N) :
    for j in range(N) :
      print(ranset(0, 9), end='')
    print()
  
