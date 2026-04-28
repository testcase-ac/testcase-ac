import sys
r = sys.stdin.readline

n = int(r())
q = list(map(float, r().split()))
r = list(map(float, r().split()))
for i in range(n - 2, -1, -1): r[i] += r[i + 1]

v = [q[i] / r[i] for i in range(n)]
v_sum = sum(v)
p = [v[i] / v_sum for i in range(n)]
print(' '.join(map(str, p)))
