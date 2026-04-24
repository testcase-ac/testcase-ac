# Generate a maximum test case for the sushi‐belt problem
# N = max number of plates, d = max sushi types,
# k = max window size, c = coupon type (choose 1 for simplicity)

N, d, k, c = 30000, 3000, 3000, 1
print(N, d, k, c)
# Arrange the belt by repeating 1…d exactly 10 times so that every k‐window
# contains all d types (cycle length == k), ensuring O(N) size and complexity.
for i in range(N):
    print(i % d + 1)
