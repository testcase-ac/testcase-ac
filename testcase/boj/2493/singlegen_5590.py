# Generate maximum testcase for the “tower laser” problem:
# N = 500,000, heights strictly within [1, 1e8], simple decreasing order
N = 500000
print(N)
# Heights from N down to 1 (each h[i] < 1e8 and N ≤ 500k)
# This makes each tower see the immediately previous taller one.
for i in range(N, 0, -1):
    print(i, end=' ' if i > 1 else '\n')
