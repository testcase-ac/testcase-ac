import random as r
import sys

if len(sys.argv) > 1:
    r.seed(sys.argv[1])

print(r.randint(1,11172))
