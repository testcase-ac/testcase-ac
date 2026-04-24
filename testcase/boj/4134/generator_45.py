import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

from random import randint, random, choice

MX = 4*10**9
print(1)
rnd = random()
if rnd < 0.2:
  print(choice([i for i in range(10)]))
elif rnd < 0.3:
  print(randint(MX-5, MX))
else:  
  print(randint(10, 10000))
