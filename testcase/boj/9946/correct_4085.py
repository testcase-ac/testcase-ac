i = 0
while 1:
    i += 1
    a = input()
    if a == 'END':
        break
    b = input()
    print('Case %d: %s' % (i, 'same' if sorted(a) == sorted(b) else 'different'))
