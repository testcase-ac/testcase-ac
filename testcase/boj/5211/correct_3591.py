s = input().split('|')
t = sum(1 for i in s if i[0] in 'CFG')
p = sum(1 for i in s if i[0] in 'ADE')
if t == p:
    print('C-major' if s[-1][-1] in 'CFG' else 'A-minor')
else:
    print('C-major' if t > p else 'A-minor')
