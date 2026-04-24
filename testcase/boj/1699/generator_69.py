import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import random, randint
r = random()
MX = 100000
if r < 0.15:
  print(randint(1, 10))
elif r < 0.4:
  print(randint(11, 100))
else:
  print(randint(101, MX))
