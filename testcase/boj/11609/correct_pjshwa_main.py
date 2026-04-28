import sys

n = int(input())
name_list = []
for i in range(n):
    name_list.append(sys.stdin.readline().rstrip().split())
    
name_list = sorted(name_list, key = lambda x: (x[1], x[0]))
for name in name_list:
    print("{} {}".format(name[0], name[1]))