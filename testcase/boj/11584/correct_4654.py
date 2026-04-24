from fractions import Fraction

from sys import stdin, stdout
input = stdin.readline
print = stdout.write
n = int(input())


while n:
    beg = Fraction(0, 1)
    stp = Fraction(1, 3)
    a, b = map(int, input().split())
    num = Fraction(a, b)
    ans = -1
    if not (0 <= num <= 1):
        ans = 0
    else:
        for i in range(1, 11):
            l = beg + stp
            r = beg + 2 * stp
            if l < num < r:
                ans = i
                break
            elif num <= l:
                stp = stp / 3
            elif num >= r:
                beg = r
                stp = stp / 3
    print(f'{ans}\n')

    n -= 1
