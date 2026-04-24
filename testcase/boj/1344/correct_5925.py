from math import factorial as ft


def comb(a, b):
    return ft(a)//ft(b)//ft(a-b)


def f(p, i):
    return p**i * (1-p)**(18-i) * comb(18, i)


a = int(input())
b = int(input())
a /= 100
b /= 100
pa, pb = 0, 0

for i in [2, 3, 5, 7, 11, 13, 17]:
    pa += f(a, i)
    pb += f(b, i)

print('%.10f' % (pa+pb-pa*pb, ))
