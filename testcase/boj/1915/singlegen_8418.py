# Generates a worst-case input for the given (wrong) solution that leads to TLE (non-AC).
# The algorithm iteratively grows squares and in an all-ones grid of size 1000x1000,
# it performs roughly sum_{k=1..999} (1000-k)^2 ≈ 3.33e8 iterations, which is too slow in Python.

def main():
    n, m = 1000, 1000
    print(f"{n} {m}")
    row = "1" * m
    for _ in range(n):
        print(row)

if __name__ == "__main__":
    main()
