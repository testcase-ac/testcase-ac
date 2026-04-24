n = int(input())
print('\n'.join('*'*(-abs(n-i-1)+n) for i in range(2*n-1)))
