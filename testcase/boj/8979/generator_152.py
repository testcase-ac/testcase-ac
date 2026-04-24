import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random, shuffle
N = randint(1, 6)
K = randint(1, N)
ls = [i+1 for i in range(N)]
shuffle(ls)

print(N, K)
for c in ls:
    print(c, randint(0, 5), randint(0, 5), randint(0, 5))
