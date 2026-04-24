n = int(input())
for i in range(n):
    ls = input().split()
    k = float(ls[0])
    for c in ls[1:]:
        if c == '@':
            k *= 3
        elif c == '%':
            k += 5
        elif c == '#':
            k -= 7
    print('%.2f' % k)
    
    
