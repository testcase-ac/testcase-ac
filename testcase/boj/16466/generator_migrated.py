import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint
ransam = random.sample

Type = ranset(0, 40)
N, ranlist = 0, []
if Type%10 <= 8 and Type != 40 :
  N = ranset(1, 10)
else :
  N = ranset(1, 1000000)
print(N)

if Type == 40:
  ranlist = ransam(range(1, 2**31-1), N)
elif Type/10 <= 2 :
  ranlist = ransam(range(1, N*4//3+1), N)
else :
  ranlist = ransam(range(1, N*2+1), N)
for i in range(N) :
  print(ranlist[i], end="\n" if i == N - 1 else " ")
