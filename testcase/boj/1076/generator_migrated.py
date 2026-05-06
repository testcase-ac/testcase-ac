import sys
import random
if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))
from random import randint

colorList = ["black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "grey", "white"]

print(colorList[randint(0, 9)])
print(colorList[randint(0, 9)])
print(colorList[randint(0, 9)])
