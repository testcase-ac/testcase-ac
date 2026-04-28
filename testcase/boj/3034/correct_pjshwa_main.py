import sys

n, w, h = map(int, sys.stdin.readline().split())
    
sq = w**2 + h**2
for _ in range(n):
    if int(input())**2 > sq:
        print("NE")
    else:
        print("DA")
