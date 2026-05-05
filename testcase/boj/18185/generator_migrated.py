import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

N = random.randint(3, 7)
print(N)
for i in range(N) :
  print(random.randint(1, 9), end=" ")
