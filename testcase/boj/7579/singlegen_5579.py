# Generate a maximal test where N is at its limit, M is at its upper bound,
# and every app’s memory usage and cost are large so that simple DP over M (size 10^7+1) will TLE/MLE.
N = 100
M = 10**7
print(N, M)
# Each app has m_i = 100000 so total memory = 100 * 100000 = 10^7 = M,
# forcing the solver to pick all apps. Cost c_i = 100 so sum of costs = 10000.
print(" ".join(["100000"] * N))
print(" ".join(["100"] * N))
