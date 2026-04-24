n = int(input())
[print(' '*(n-i) +' '.join('*' for _ in range(i))) for i in range(1, n+1)]
