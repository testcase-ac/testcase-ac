import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

T, Nlim = 0, 0
Type = ranset(1, 10)
if Type <= 9 :
  T = ranset(1, 3)
  Nlim = 5
else :
  T = ranset(1, 50)
  Nlim = 1000

for i in range(T):
  N = ranset(1, Nlim)
  N *= 2
  for j in range(N) :
    lr = ranset(1, 2)
    if lr == 1 :
      print("{", end="")
    else :
      print("}", end="")
  print()
for i in range(ranset(1, 10)) :
  print("-", end="")
print()
