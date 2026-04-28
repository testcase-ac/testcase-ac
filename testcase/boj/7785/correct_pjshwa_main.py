exec(compile('''
import sys;r=sys.stdin.readline;geegle_p={};n=int(r())
for _ in range(n):
    ops = r().rstrip().split()
    if ops[1] == 'enter': geegle_p[ops[0]] = 1
    else: geegle_p[ops[0]] = 0
in_list = (x for x,v in geegle_p.items() if v==1)
for item in sorted(in_list)[::-1]: print(item)
''','<string>','exec'))