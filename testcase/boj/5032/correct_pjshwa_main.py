import sys

e, f, c = map(int, sys.stdin.readline().split())
e += f
free_drinks = 0
while(e >= c):
    e -= c
    e += 1
    free_drinks += 1
print(free_drinks)