import sys
r=sys.stdin.readline
n=int(r())
nums = []
for _ in range(n):
    nums.append(list(map(int, r().split())))
plus_max = max(map(lambda x: x[0]+x[1], nums))
plus_min = min(map(lambda x: x[0]+x[1], nums))
minus_max = max(map(lambda x: x[0]-x[1], nums))
minus_min = min(map(lambda x: x[0]-x[1], nums))
print(max(plus_max-plus_min, minus_max-minus_min))