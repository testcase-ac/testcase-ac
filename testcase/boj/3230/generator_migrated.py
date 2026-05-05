import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

Type = ranset(1, 5)
N, M = 0, 0

if Type <= 4 :
  N = ranset(3, 7)
else :
  N = ranset(3, 100)
M = ranset(3, N)
print(N, M)

Sum = 1
for i in range(N) :
  print(ranset(1, Sum))
  Sum += 1
Sum = 1
for i in range(M) :
  print(ranset(1, Sum))
  Sum += 1
