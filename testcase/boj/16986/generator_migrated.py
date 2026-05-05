import random
ranset = random.randint
ransam = random.sample

Type = ranset(1, 8)
N, K = 0, 0

if Type <= 7 :
  N = ranset(1, 4)
  K = ranset(1, N+1)
else :
  N = ranset(1, 9)
  K = ranset(1, min(6, N))

List = [[0]*N for i in range(N)]
for i in range(N) :
  List[i][i] = 1
for i in range(1, N) :
  for j in range(i) :
    val = ranset(0, 1)
    if val == 0 :
      List[i][j] = 0
      List[j][i] = 2
    else :
      List[i][j] = 2
      List[j][i] = 0

print(N, K)
for i in range(N) :
  for j in range(N) :
    print(List[i][j], end=" ")
  print()
for i in range(20) :
  print(ranset(1, N), end=" ")
print()
for i in range(20):
  print(ranset(1, N), end=" ")
