# Generate maximum testcase for the circular paint-house problem with N=1000
# Each line has three costs in [1,1000], varied but deterministic.
N = 1000
print(N)
for i in range(1, N+1):
    # deterministic pseudo-random costs to cover all edge patterns
    c1 = (i * 123 +  45) % 1000 + 1
    c2 = (i * 456 +  78) % 1000 + 1
    c3 = (i * 789 +  90) % 1000 + 1
    print(c1, c2, c3)
