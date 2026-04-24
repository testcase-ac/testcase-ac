# Generate a maximum-size test case for the interval-scheduling problem.
# N = 100000, times stay within 2^31−1, and none of the 100k meetings overlap.
N = 100000
print(N)
for i in range(N):
    t = i * 20000
    print(t, t + 1)
