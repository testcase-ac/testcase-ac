exec(compile('''remainder_set = set();import sys;r=sys.stdin.readline
for _ in range(10):
 n=int(r());remainder_set.add(n%42)
print(len(remainder_set))''','<string>','exec'))