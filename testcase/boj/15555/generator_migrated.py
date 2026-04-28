import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

n,m=random.randint(1,1000),random.randint(1,1000)
print(n,m)
l=['R','G','W']
for i in range(n):
  for j in range(m):
    print(random.choice(l),end='')
  print()
