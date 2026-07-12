import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

N = random.randint(1, 10)
print(N)
mink = 51
prices = []
for _ in range(N):
    P = random.randint(1, 50)
    prices.append(P)
    if P < mink:
        mink = P
print(*prices)
M = 0
while M < mink:
    M = random.randint(1, 50)
print(M)
