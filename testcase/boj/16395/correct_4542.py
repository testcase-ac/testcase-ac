from math import factorial as f
n, k = map(int, input().split())
print(f(n-1)//f(k-1)//f(n-k))
