import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random, choice
choices = ['#', '*', '.']

def gen_tc():
    R, C = randint(3, 10), randint(3, 10)
    print(C, R)
    weight = [random(), random(), random()]
    weight[1] /= randint(1, 5)
    weight[0] /= randint(1, 5)
    weight_acc = [sum(weight[:i+1]) for i in range(3)]
    def choice_rnd():
        rnd = random() * weight_acc[-1]
        for i, w in enumerate(weight_acc):
            if rnd < w:
                return choices[i]
    arr = [[choice_rnd() for _ in range(C)] for _ in range(R)]
    while True:
        r = randint(0, R-1)
        c = randint(0, C-1)
        if r == 0 or c == 0 or r == R-1 or c == C-1 and random() < 0.2:
            continue
        else:
            break
    arr[r][c] = '@'
    for ls in arr:
        print(''.join(ls))
    

T = randint(1, 2)
print(T)
for i in range(T):
    gen_tc()
