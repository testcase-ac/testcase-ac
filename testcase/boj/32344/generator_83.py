import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, shuffle, choice
R, C = randint(1, 5), randint(1, 5)
N = randint(1, R*C)
print(R, C)
print(N)
ls = [i for i in range(1, N+1)]
shuffle(ls)
ls = ls[:randint(1, N)]
for i in range(N):
    print(choice(ls), randint(1, R), randint(1, C))
