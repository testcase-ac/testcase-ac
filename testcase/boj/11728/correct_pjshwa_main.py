import sys

max_a, max_b = map(int, sys.stdin.readline().split())
idx_a, idx_b = 0, 0
a = list(map(int, sys.stdin.readline().split()))
b = list(map(int, sys.stdin.readline().split()))

while(idx_a != max_a and idx_b != max_b):
    if(a[idx_a] > b[idx_b]):
        print(b[idx_b],'', end="")
        idx_b += 1
    else:
        print(a[idx_a],'' ,end="")
        idx_a += 1
while(idx_a != max_a):
    print(a[idx_a],'', end="")
    idx_a += 1
while(idx_b != max_b):
    print(b[idx_b],'', end="")
    idx_b += 1