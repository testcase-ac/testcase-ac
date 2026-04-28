n = int(input())
a = i = 1
lb = 10 ** (n - 1)
ub = lb * 10
ans = []

while True:
  a *= i
  if a >= lb and a < ub: ans.append(i)
  if a >= ub: break
  i += 1

if len(ans):
  print(len(ans))
  for el in ans: print(el)
else:
  print('NO')
