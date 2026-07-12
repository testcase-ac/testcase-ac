import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

def fecto(n) :
    Sum = 1
    for i in range(1, n+1):
        Sum *= i
    return Sum

Type = ranset(0, 99)
List = [1 for _ in range(50)]
Ranlist = [0 for _ in range(50)]
N, K = 0, 0

if Type % 20 <= 7 :
    N = ranset(1, 5)
    K = ranset(1, 5)
elif Type % 20 <= 15 :
    N = ranset(1, 10)
    K = ranset(1, 20)
elif Type % 20 <= 17 :
    N = ranset(1, 45)
    if Type % 20 == 16 :
        K = ranset(1, N*(N+1)//2)
    else :
        K = ranset(1, 1000000)
else :
    N = ranset(46, 50)
    if Type % 20 == 18 :
        K = ranset(1, N*(N+1)//2)
    else :
        K = ranset(1, 1000000)

if Type / 20 > 3 :
    if Type <= 95 :
        Ranlist = random.sample(range(1, 51), N)
    else :
        Ranlist = random.sample(range(1, 1000001), N)
Ranlist = Ranlist[:N]
Ranlist.sort()

print(N)
Order = ranset(0, fecto(N) - 1)
for i in range(N, 0, -1) :
    In = 0
    Minus = fecto(i - 1)
    while Order >= Minus :
        Order -= Minus
        In += 1
    In2 = 0
    while In != 0 or List[In2] == 0 :
        if List[In2] == 1 :
            In -= 1
        In2 += 1
    if Type / 20 <= 3 :
        print(In2 + 1, end="\n" if i == 1 else " ")
    else :
        print(Ranlist[In2], end="\n" if i == 1 else " ")
    List[In2] = 0
print(K)
