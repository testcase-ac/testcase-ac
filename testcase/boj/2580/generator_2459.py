import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

#!/usr/bin/env python3
"""
Simple Sudoku generator for the BOJ 2580 task.
    $ python gen.py [seed] [clues]

seed   : optional int — RNG seed for reproducibility
clues  : optional int — number of pre‑filled cells (default 40)

The program prints nine lines of nine numbers (0 = blank).
"""

import sys, random

# ------------------------------------------------------------
#  Back‑tracking routine to build a *complete* random grid
# ------------------------------------------------------------
def is_safe(g, r, c, v):
    if v in g[r] or any(g[i][c] == v for i in range(9)):
        return False
    br, bc = 3 * (r // 3), 3 * (c // 3)
    for i in range(3):
        for j in range(3):
            if g[br + i][bc + j] == v:
                return False
    return True


def fill(g, idx=0):
    if idx == 81:
        return True
    r, c = divmod(idx, 9)
    if g[r][c]:
        return fill(g, idx + 1)
    nums = list(range(1, 10))
    random.shuffle(nums)
    for v in nums:
        if is_safe(g, r, c, v):
            g[r][c] = v
            if fill(g, idx + 1):
                return True
            g[r][c] = 0
    return False


# ------------------------------------------------------------
#  Generate: complete grid → remove cells
# ------------------------------------------------------------
def generate(seed=None):
    random.seed(seed)
    grid = [[0] * 9 for _ in range(9)]
    fill(grid)                          # step 1: full solution

    # step 2: knock out 81‑clues cells, keeping exactly “clues” left
    cells = list(range(81))
    random.shuffle(cells)
    clues = random.randint(25, 81)
    for idx in cells[:-clues]:
        r, c = divmod(idx, 9)
        grid[r][c] = 0
    return grid


if __name__ == "__main__":
    seed  = int(sys.argv[1]) if len(sys.argv) > 1 else None

    puzzle = generate(seed)
    for row in puzzle:
        print(" ".join(map(str, row)))
