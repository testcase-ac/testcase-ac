import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint

n = randint(2, 10)
arr = [randint(-9, 9) for i in range(n)]
print(n)
print(*arr)
