import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random

def gen_tc():
    N, M = randint(2, 12), randint(2, 12)

    ls = [random(), random()]
    ls.sort()
    def gen():
        r = random()
        if r < ls[0]:
            return -1
        elif r < ls[1]:
            return 0
        else:
            return 1

    arr = [[gen() for _ in range(N)] for _ in range(M)]
    ok = False
    for i in range(M):
        for j in range(N):
            if arr[i][j] == 1:
                ok = True
    if not ok:
        i, j = randint(0, M - 1), randint(0, N - 1)
        arr[i][j] = 1
    
    print(N, M)
    for i in range(M):
        print(*arr[i])
        
if __name__ == '__main__':
    gen_tc()
