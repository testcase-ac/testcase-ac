# Generates a worst-case valid test for the problem that triggers the wrong solution's
# off-by-one buffer overflow (K=100000 uses arr[100000]) and also its quadratic scan,
# likely causing RE/TLE.

def main():
    K = 100000
    print(K)
    # First 50,000 ones, then 50,000 zeros.
    # Each zero has a previous number to remove; final sum should be 0.
    for _ in range(50000):
        print(1)
    for _ in range(50000):
        print(0)

if __name__ == "__main__":
    main()
