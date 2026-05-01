# Generate a single test case: one string of length 1000 (the maximum allowed).
# We cycle through 'a' to 'z' to keep it simple yet maximize length.
s = ''.join(chr(ord('a') + i % 26) for i in range(1000))
print(s)
