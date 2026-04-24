import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random
R, C = randint(2, 5), randint(2, 5)
print(R, C)
one_density = random()
for i in range(R):
    ls = [1 if random() < one_density else randint(2, 5) for _ in range(C)]
    print(*ls)
