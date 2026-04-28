# https://www.acmicpc.net/source/33803240 by ho94949

N = int(input())
K = (N - (6 if N%2 == 0 else 3)) // 2

ans = 0
if K >= 0:
    X = (K+2)*(K+1)//2
    Y = K // 2 + 1
    Z = 1 if K%3 == 0 else 0
    ans = (X+3*Y+2*Z) // 6

print(ans)
