import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random
R, C = randint(4, 6), randint(4, 6)
repr_num = randint(1, 9)
repr_freq = random()
def choose():
    r = random()
    if r < repr_freq:
        return repr_num
    else:
        return randint(1, 9)

table = [[choose() for _ in range(C)] for _ in range(R)]
print(R, C)
for row in table:
    print(*row)
