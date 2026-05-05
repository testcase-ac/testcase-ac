import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

N = random.randint(1, 50)
Ksum = 2**N
K = random.randint(0, Ksum-1)
print(N, K)
