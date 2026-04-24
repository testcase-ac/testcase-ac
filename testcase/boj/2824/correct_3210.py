from math import gcd
from functools import reduce
def get():
    return reduce(lambda a, b: a*b, map(int, input().split()))
input()
a = get()
input()
b = get()
g = str(gcd(a, b))
if len(g) > 9:
    print(g[-9:])
else:
    print(g)
