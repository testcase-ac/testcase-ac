import random
import string
import sys

if len(sys.argv) > 1:
    random.seed(sys.argv[1])

a=random.randint(1, 50)
print(a)
b=''
for i in range(a):
    b+=random.choice("abcdefghijklmnopqrstuvwxyz")


print(b)
