# Generate a maximum-size test case for the problem
# N = 800, E = 200000, chain of light edges (weight=1),
# plus many heavy filler edges (weight=1000). Must pass through v1=100, v2=700.

N = 800
E = 200000
v1, v2 = 100, 700

print(N, E)
# 1) print a simple chain from 1 to N with weight=1
for i in range(1, N):
    print(i, i + 1, 1)

# 2) add heavy edges (weight=1000) to reach E edges total
#    skip the chain edges (i, i+1)
remaining = E - (N - 1)
i = 1
j = 3
while remaining > 0 and i <= N:
    if j > N:
        i += 1
        j = i + 2
        continue
    # skip chain edges (i, i+1)
    if j != i + 1:
        print(i, j, 1000)
        remaining -= 1
    j += 1

# 3) finally, the two required intermediate vertices
print(v1, v2)
