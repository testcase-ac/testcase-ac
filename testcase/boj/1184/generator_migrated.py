import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

N = random.randint(1,50);
print(N)
for _ in range(N):
    row = [str(random.randint(-999,999)) for _ in range(N)]
    print(" ".join(row))
