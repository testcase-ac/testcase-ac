# Generates a maximal test of size N = 200000.
# Edges (front 3–9 cycle and back 3–9 cycle) force removal,
# the only valid max-length subarray with ≤2 types is the middle 100000 elements of 1s and 2s.
N = 200000
print(N)
# Front 60k of types 3–9 cycling
front = [(i % 7) + 3 for i in range(60000)]
# Middle 100k of alternating 1 and 2
middle = [1, 2] * 50000
# Back 40k of types 3–9 cycling
back = [((i + 5) % 7) + 3 for i in range(40000)]
seq = front + middle + back
print(*seq)
