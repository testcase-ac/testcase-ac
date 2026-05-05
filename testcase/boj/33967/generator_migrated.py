import random
ranset = random.randint

Type = ranset(1, 6)
N = 0
if Type <= 5 :
  N = ranset(2, 10)
else :
  N = ranset(2, 200000)
print(N)

kanlist = ['[', '5', '2', ']']
print("[", end="")
for i in range(N-2) :
  kan = ranset(0, 3)
  print(kanlist[kan], end="")
print("]", end="")
