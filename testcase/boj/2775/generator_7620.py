import random
import sys
if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

from random import randint

T = randint(1,3)
print(T)
for i in range(T):
  print(randint(1,14))
  print(randint(1,14))
