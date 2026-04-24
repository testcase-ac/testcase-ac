import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random
C, R, H = randint(2, 5), randint(2, 5), randint(1, 3)
def gen_table():
    th = [random(), random()]
    th.sort()
    def pick():
        r = random()
        if r < th[0]:
            return -1
        elif r < th[1]:
            return 0
        else:
            return 1
    table = [[pick() for _ in range(C)] for _ in range(R)]
    return table

print(C, R, H)
tables = []
all_n1 = True
for i in range(H):
    tb = gen_table()
    if any(any(x != -1 for x in row) for row in tb):
        all_n1 = False
    tables.append(tb)

if all_n1:
    r, c, h = randint(0, R-1), randint(0, C-1), randint(0, H-1)
    tables[h][r][c] = randint(0, 1)

for tb in tables:
    for row in tb:
        print(*row)
