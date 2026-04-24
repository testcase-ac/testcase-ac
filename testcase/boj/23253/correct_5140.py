import sys

input = sys.stdin.readline

n, m = map(int, input().split())

for _ in range(m):
    input()
    ls = list(map(int, input().split()))
    for i in range(1, len(ls)):
        if ls[i] > ls[i-1]:
            print('No')
            exit()

print('Yes')
