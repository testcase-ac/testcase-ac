import re
pt = re.compile('(100+1+|01)+$')
print('SUBMARINE' if pt.match(input()) else 'NOISE')
