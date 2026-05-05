import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

N = random.randint(1, 1000000000)
L = random.randint(2, 100)
print(N, L)
