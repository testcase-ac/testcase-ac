import sys
ls = [int(i) for i in ''.join(l.strip() for l in sys.stdin).split(',')]
print(sum(ls))
