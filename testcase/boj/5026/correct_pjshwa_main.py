import sys

n = int(input())
for _ in range(n):
    s = sys.stdin.readline().rstrip()
    if(s == "P=NP"):
        print("skipped")
    else:
        s = map(int, s.split("+"))
        print(sum(s))