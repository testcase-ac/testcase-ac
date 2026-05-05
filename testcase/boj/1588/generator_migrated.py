import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

Type = ranset(1, 3)
N, L, R = 0, 0, 0
print(ranset(1, 3))
if Type <= 2 :
  N = ranset(0, 2)
  L = ranset(0, 3**N-1)
  R = ranset(0, 3**N-1)
else :
  N = ranset(0, 20)
  L = ranset(0, min(3**N-1, 2147483647))
  R = ranset(0, min(3**N-1, 2147483647))
if L > R :
  temp = L
  L = R
  R = temp
print(L)
print(R)
print(N)
