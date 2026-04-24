import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random, choice
# 1 4 2 1
N = randint(1, 10)
op_ls = ['add', 'remove', 'check', 'toggle', 'all', 'empty']
weights = [random() for _ in range(6)]
weight_acc = [sum(weights[:i+1]) for i in range(6)]
ls = []
has_out = False
num_lb = 1
num_ub = randint(1, 20)
sticky_prob = random()
used_num = []
for _ in range(N):
    w = random() * weight_acc[-1]
    op = op_ls[next(i for i in range(6) if w < weight_acc[i])]
    if op in ['add', 'remove', 'check', 'toggle']:
        num = randint(num_lb, num_ub) if (random() < sticky_prob or not used_num) else choice(used_num)
        ls.append(f'{op} {num}')
        used_num.append(num)
    else:
        ls.append(op)
    if op in ['check']:
        has_out = True

if not has_out:
    ls.append(f'check {randint(num_lb, num_ub)}')
    
print(len(ls))
for l in ls:
    print(l)
