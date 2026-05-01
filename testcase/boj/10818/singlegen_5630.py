# Generates the largest possible test for the min/max problem:
# N = 1,000,000, values in [−10^6,10^6], including both extremes.
N = 10**6
print(N)
# First value −10^6, last value +10^6, fill the rest with zeros.
print(-10**6, *([0] * (N - 2)), 10**6)
