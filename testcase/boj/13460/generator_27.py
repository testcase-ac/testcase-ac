import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random, shuffle
while True:
    R, C = randint(4, 10), randint(4, 10)
    space = (R - 2) * (C - 2)
    if space >= 3:
        break
    
board = [['#' if c == 0 or c == C-1 or r == 0 or r == R-1 else '.' for c in range(C)] for r in range(R)]
density = random()
ls = []
for r in range(1, R-1):
    for c in range(1, C-1):
        ls.append((r, c))
        rnd = random()
        if rnd < density:
            board[r][c] = '#'
shuffle(ls)
board[ls[0][0]][ls[0][1]] = 'O'
board[ls[1][0]][ls[1][1]] = 'R'
board[ls[2][0]][ls[2][1]] = 'B'
print(R, C)
for row in board:
    print(''.join(row))
