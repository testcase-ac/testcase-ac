a, b = input().split()
n = int(input())
for i in range(n):
    sa, sb = 0, 0
    ls = input().split()
    ok = True
    for m in ls:
        l, r = map(int, m.split(':'))
        lwin = l > r
        if not lwin:
            l, r = r, l
        if l == r:
            ok = False
        if sa == 1 and sb == 1:
            if l >= 7:
                if l-r != 2:
                    ok = False
            elif l == 6:
                if r == 5:
                    ok = False
            else:
                ok = False
        else:
            if l == 7:
                if r < 5:
                    ok = False
            elif l == 6:
                if r == 5:
                    ok = False
            else:
                ok = False
        if sa == 2 or sb == 2:
            ok = False
        if lwin:
            sa += 1
        else:
            sb += 1
    if (a == 'federer' and sb) or (b == 'federer' and sa) or not(sa == 2 or sb == 2):
        ok = False
    print('da' if ok else 'ne')
