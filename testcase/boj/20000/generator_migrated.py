import random
import sys

if len(sys.argv) > 1:
    random.seed(sys.argv[1])

print(random.randint(0,9))
