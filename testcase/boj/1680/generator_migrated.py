import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint
ransor = random.sample

Type = ranset(1, 10)
Tlim, Wlim, Nlim, Xlim = 0, 0, 0, 0
if Type <= 5 :
  Tlim, Wlim, Nlim = 2, 7, 5
  Xlim = ranset(Nlim, Nlim+4)
elif Type <= 9 :
  Tlim, Wlim, Nlim = 5, 20, 15
  Xlim = ranset(Nlim, Nlim+10)
else :
  Tlim, Wlim, Nlim = 100, 1000, 1000
  Xlim = ranset(Nlim, 100000)
  
T = ranset(1, Tlim)
print(T)
for i in range(T) :
  W, N = ranset(1, Wlim), ranset(1, Nlim)
  List = ransor(range(Xlim), N)
  List.sort()
  print(W, N)
  for j in range(N) :
    print(List[j], ranset(1, W))
