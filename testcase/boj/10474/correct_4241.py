while 1:
    a,b=map(int,input().split())
    if not a and not b:
        break
    print('%d %d / %d' % (a//b, a%b, b))
