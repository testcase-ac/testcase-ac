import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

N = random.randint(1,50);
print(N)
for _ in range(N):
    for _ in range(N):
        K = random.randint(-999,999)
        print(K, end=" ")
    print(" ")
