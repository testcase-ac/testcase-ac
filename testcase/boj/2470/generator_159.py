import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, shuffle

N = randint(2, 8)
lb = -10
ub = 10
ls = list(range(lb, 0)) + list(range(1, ub+1))
shuffle(ls)
print(N)
print(*ls[:N])
