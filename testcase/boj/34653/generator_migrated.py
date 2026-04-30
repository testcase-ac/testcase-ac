import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

from random import randint,sample
n=randint(1,200000)
print(n)
l=sample(range(1,10**9+1),n)
L=set(l)
l.sort()
for i in range(n):
    print(l[i],randint(1,10**9+1))
m=randint(1,200000)
print(m)
for i in range(m):
    p=randint(l[0]+1,l[-1]-1)
    while p in L:p=randint(l[0]+1,l[-1]-1)
    print(p)
