import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

print(random.randint(1, 100))
