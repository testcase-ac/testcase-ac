# Generates a test where the wrong solution overflows its LIS count (64-bit signed)
# Construct 63 blocks of size 2, each block in decreasing order, blocks increasing by value.
# Number of LIS = 2^63 (> 9e18), which overflows signed long long in the wrong code,
# causing it to print -1 even for K=1.

def main():
    N = 126  # 63 blocks of 2
    K = 1
    seq = []
    for x in range(1, N + 1, 2):
        seq.append(x + 1)
        seq.append(x)
    print(f"{N} {K}")
    print(" ".join(map(str, seq)))

if __name__ == "__main__":
    main()
