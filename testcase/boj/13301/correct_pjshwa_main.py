import sys
r = sys.stdin.readline

n = int(r())

a = 0
b = 1
c = 1
for i in range(n - 1):
    c = a + b
    a, b = b, c
    
if n == 1: print("4")
else: print(2*(a+2*b))