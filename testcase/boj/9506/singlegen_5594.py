# Generate the largest possible set of test‐inputs:
# one number per line, from 3 up to 99999 (since n < 100000),
# then terminate with -1.

for n in range(3, 100000):
    print(n)
print(-1)
