C = [0, 0, 0, 0]

input()
for x in map(int, input().split()): C[x] += 1

ans = 0
while C[0] > 0 and C[3] > 0:
  ans += 3
  C[0] -= 1
  C[3] -= 1

while C[1] > 0 and C[2] > 0:
  ans += 3
  C[1] -= 1
  C[2] -= 1

for i in range(4):
  for j in range(i + 1, 4):
    while C[i] > 0 and C[j] > 0:
      ans += (i ^ j)
      C[i] -= 1
      C[j] -= 1

print(ans)
