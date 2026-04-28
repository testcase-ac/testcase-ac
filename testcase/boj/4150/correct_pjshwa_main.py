fib_array = [-1] * 5000

import sys
sys.setrecursionlimit(10 ** 6)

def fib(n):
    if n == 0: return 0
    elif n == 1: return 1
    if fib_array[n-1] == -1:
        fib_array[n-1] = fib(n-1) + fib(n-2)
    return fib_array[n-1]

print(fib(int(input())))