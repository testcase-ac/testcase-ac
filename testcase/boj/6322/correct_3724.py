from math import sqrt
for i in range(1, 10**9):
    a, b, c = map(int, input().split())
    if not a and not b and not c:
        break
    if i != 1:
        print()
    print(f'Triangle #{i}')
    ok = False
    if a == -1:
        v = c*c - b*b
        if v > 0:
            ok = True
            print('a = %.3f' % sqrt(v))
    elif b == -1:
        v = c*c-a*a
        if v > 0:
            ok = 1
            print('b = %.3f' % sqrt(v))
    else:
        v = a*a+b*b
        if v > 0:
            ok = 1
            print('c = %.3f' % sqrt(v))
    if not ok:
        print('Impossible.')
