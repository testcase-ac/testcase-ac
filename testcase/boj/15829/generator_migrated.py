import random
import string

a=random.randint(1, 50)
print(a)
b=''
for i in range(a):
    b+=random.choice("abcdefghijklmnopqrstuvwxyz")


print(b)
