# Maximum test: T = 1000, and each pair is the two largest allowed values with gcd = 1
# so that lcm = 45000 * 44999 is as large as possible without overflow.
print(1000)
for _ in range(1000):
    print(45000, 44999)
