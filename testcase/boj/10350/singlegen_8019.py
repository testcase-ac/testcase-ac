# Generates a test causing the wrong solution to run out of memory due to massive ksum allocation
# Wrong solution allocates vector<ll> ksum(120000 * n), which for n=9999 is ~9.6 GB
# This valid test (n<10000, ki in range, total sum positive) will trigger MLE.

def main():
    n = 9999
    print(n)
    # All ones: sum is positive, values within [-31999,31999]
    print(" ".join(["1"] * n))

if __name__ == "__main__":
    main()
