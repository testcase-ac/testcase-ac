import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint
lim = ranset(9, 20)
N, M = ranset(1, 10), ranset(5, 20)
print(N)
Nlist = [lim]
for i in range(N-1) :
    Nlist.append(ranset(1, lim))
Nlist.sort(reverse=True)
print(*Nlist)
print(M)
Mlist = []
for i in range(M) :
    Mlist.append(ranset(1, lim))
Mlist.sort(reverse=True)
print(*Mlist)
