import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

Type = ranset(1, 10)
N, M = 0, 0

if Type <= 7 :
  N = ranset(1, 7)
  M = ranset(1, 6)
  print(N, M)
  time = ranset(0, 6)
  for i in range(N) :
    time += ranset(1, M*2)
    print(time, end=" ")
else :
  N = ranset(1, 1000000)
  if Type <= 9 :
    M = ranset(1, 50)
  else :
    M = ranset(1, 1000000)
  print(N, M)
  List = random.sample(range(1, 1000001), N)
  List.sort()
  for i in range(N) :
    print(List[i], end=" ")
