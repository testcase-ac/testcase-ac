import random
ranset = random.randint
lim = ranset(9, 20)
N, M = ranset(1, 10), ranset(5, 20)
print(N)
Nlist = []
print(lim, end=" ")
for i in range(N-1) :
    Nlist.append(ranset(1, lim))
Nlist.sort(reverse=True)
for i in range(N-1) :
    print(Nlist[i], end=" ")
print()
print(M)
Mlist = []
for i in range(M) :
    Mlist.append(ranset(1, lim))
Mlist.sort(reverse=True)
for i in range(M) :
    print(Mlist[i], end=" ")
