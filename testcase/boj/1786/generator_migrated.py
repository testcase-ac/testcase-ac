import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

lenP = random.randint(1, 10)
lenT = 998 - lenP
T = "".join(random.choices("ab", k=lenT))
P = "".join(random.choices("ab", k=lenP))
print(T)
print(P)
