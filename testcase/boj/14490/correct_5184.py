def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


a, b = map(int, input().split(':'))
g = gcd(a, b)
print(f'{a//g}:{b//g}')
