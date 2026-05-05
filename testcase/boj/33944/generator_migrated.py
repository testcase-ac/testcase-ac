import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint
ransam = random.sample

Type = ranset(0, 23)
T = 0
if Type%8 <= 6 :
  T = ranset(1, 3)
else :
  T = ranset(1, 1000)
print(T)
for _ in range(T) :
  N, K = 0, 0
  if Type%8 <= 6 :
    N = ranset(2, 20)
  else :
    N = ranset(2, 10**18)
  if Type/8 <= 1 :
    K = ranset(1, min(1000, N//2))
  else :
    K = ranset(1, min(1000, N-1))
  print(N)
  print(K)
  ranlist = ransam(range(1, N), K)
  ranlist.sort()
  for i in range(K) :
    print(ranlist[i], end=" ")
  if _ != T-1 :
    print()
