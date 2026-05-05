import random
ranset = random.randint
ransam = random.sample

Type = ranset(1, 4)
N, K, D = 0, 0, 0
L, Z = [0]*(100), [0]*(200)

if Type <= 3 :
  N = ranset(3, 6)
  K = ranset(1, 3)
  D = ranset(5, 7)
  for i in range(D) :
    L[i] = ranset(0, min(N, 4))
  for i in range(N) :
    Z[i] = ranset(1, D)
else :
  N = ranset(3, 200)
  K = ranset(1, 5)
  D = ranset(5, 100)
  for i in range(D) :
    L[i] = ranset(0, N)
  for i in range(N) :
    Z[i] = ranset(1, D)

print(N, K, D)
for i in range(D) :
  print(L[i], end=" ")
print()
for i in range(N) :
  print(Z[i], end=" ")
  C = ransam(range(1, D+1), Z[i])
  for j in range(Z[i]) :
    print(C[j], end=" ")
  print()
