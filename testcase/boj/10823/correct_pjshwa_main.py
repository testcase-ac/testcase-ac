import sys
print(sum(map(int, ''.join(sys.stdin.readlines()).replace('\n','').split(','))))