from random import randint, seed
import sys

if len(sys.argv) > 1:
  seed(sys.argv[1])

a=randint(0,3)

if a:
  n,c=randint(1,10000),randint(1,randint(2,10000))
  print(n,c)
  for i in range(c):
    print(randint(1,n),randint(1,n))
else:
  n,c=randint(1,10000),1
  print(n,c)
  print(randint(1,n),randint(1,n))
