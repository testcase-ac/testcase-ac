import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint
a1, a0 = randint(-10, 10), randint(-10, 10)
c = randint(1, 10)
n0 = randint(1, 10)
print(a1, a0)
print(c)
print(n0)
