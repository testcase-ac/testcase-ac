import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

N = random.randint(1, 40)
K = random.randint(1, N)
print(N, K)
