# Generate the “maximum” stress test:
# T = 0, n = m = 1000, all A[i]=0 and B[i]=0
# This makes every subarray‐sum of A = 0 and of B = 0,
# so the answer = (n(n+1)/2)^2 ≈ 2.5e11, and both n,m at max.
n = m = 1000
print(0)          # T
print(n)          # size of A
print(*([0]*n))   # A[1..n]
print(m)          # size of B
print(*([0]*m))   # B[1..m]
