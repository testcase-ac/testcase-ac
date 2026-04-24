# Generate a maximum-size test for the stack commands:
# N = 1_000_000 commands: first 500k pushes of the maximum X=100000, then 500k pops.
N = 10**6
print(N)
# 500,000 pushes of X = 100,000
for _ in range(N // 2):
    print("1 100000")
# 500,000 pops
for _ in range(N // 2):
    print("2")
