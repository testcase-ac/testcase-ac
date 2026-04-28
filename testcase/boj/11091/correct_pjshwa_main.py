import sys, string;r=sys.stdin.readline;n=int(r())
for _ in range(n):
    s=r().rstrip().lower()
    a = True
    li = []
    for l in string.ascii_lowercase:
        if l not in s:
            a = False
            li.append(l)
    if a: print('pangram')
    else:print('missing {}'.format(''.join(sorted(li))))