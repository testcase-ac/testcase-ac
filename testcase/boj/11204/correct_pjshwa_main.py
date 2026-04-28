MAXN = 200
C = [[0] * (MAXN + 1) for _ in range(MAXN + 1)]
P = [0] * (MAXN + 1)

N = int(input())

C[0][0] = 1
for i in range(1, N + 1):
  C[i][0] = 1
  for j in range(1, i + 1):
    C[i][j] = C[i - 1][j] + C[i - 1][j - 1]

P[2] = 1
for i in range(3, N + 1):
  total = (i - 1) ** i
  for j in range(2, i):
    total -= P[j] * C[i - 1][j - 1] * (i - j - 1) ** (i - j)
  P[i] = total

total = (N - 1) ** N
print(P[N] / total)
