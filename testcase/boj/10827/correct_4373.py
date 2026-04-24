from decimal import Decimal, getcontext
getcontext().prec = 10000
a, b = input().split()
print('{0:f}'.format(Decimal(a)**Decimal(b)))
