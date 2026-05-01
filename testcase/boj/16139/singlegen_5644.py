# Generate maximum test case for the problem:
# |S| = 200_000, q = 200_000
# We build S by cycling 'a'..'z' to length 200k,
# then issue 200k queries covering the full range [0, N-1],
# cycling the queried letter through 'a'..'z' to exercise all prefix‐sum arrays.

N = 200_000
Q = 200_000

# 1) build S of length N
S = ''.join(chr(ord('a') + (i % 26)) for i in range(N))

# 2) print S and Q
print(S)
print(Q)

# 3) print Q queries: each is "letter 0 N-1",
#    letters cycle through 'a'..'z'
for i in range(Q):
    letter = chr(ord('a') + (i % 26))
    print(letter, 0, N - 1)
