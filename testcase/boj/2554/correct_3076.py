def a(n):
    if n <= 1: return 1
    return 6*[1, 1, 2, 6, 4, 4, 4, 8, 4, 6][n%10]*3**(n//5%4)*a(n//5)%10

n = int(input())
print(a(n))
