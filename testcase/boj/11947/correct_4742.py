T = int(input())
for _ in range(T):
    n = input()
    s = int('1' + ''.join('0' for i in n))
    n = int(n)
    if s//2 >= n:
        print((s-1-n)*n)
    else:
        print((s//2-1)*s//2)
