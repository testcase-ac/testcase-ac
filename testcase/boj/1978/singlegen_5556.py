# Generate a maximum testcase for N=100 with the first 100 primes (all ≤1000)
N = 100
primes = []
x = 2
while len(primes) < N:
    for d in range(2, int(x**0.5) + 1):
        if x % d == 0:
            break
    else:
        primes.append(x)
    x += 1

print(N)
print(*primes)
