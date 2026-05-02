import sys

data = sys.stdin.read().splitlines()
first_line = data[0].split()
N = int(first_line[0])
K = int(first_line[1])
lines = data[1:1+N]

full_mask = (1 << K) - 1
exists = [False] * (1 << K)

results = []
z_prev = 0

for i in range(N):
    s = lines[i].strip()
    if z_prev == 0:
        bits = []
        for char in s:
            bits.append(char)
        num_str = ''.join(bits)
        mask = int(num_str, 2)
    else:
        bits = []
        for char in s[::-1]:
            bits.append(char)
        num_str = ''.join(bits)
        mask = int(num_str, 2)
    found = False
    sup = mask
    while True:
        if exists[sup]:
            found = True
            break
        if sup == full_mask:
            break
        sup = (sup + 1) | mask
    if found:
        results.append("WellKnown")
        z_prev = 0
    else:
        results.append("AdHoc")
        z_prev = 1
    exists[mask] = True

for res in results:
    print(res)
