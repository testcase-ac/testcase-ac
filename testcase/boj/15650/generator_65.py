import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint
m = randint(1, 8)
n = randint(m, 8)
print(n, m)
