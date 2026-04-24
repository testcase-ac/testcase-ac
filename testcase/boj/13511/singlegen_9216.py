# Generates a long chain tree with large edge weights to cause 32-bit overflow in distance computation
# The wrong solution stores distances in int32 and prints with %d, so a long path with 1e6 weights overflows.

def main():
    N = 3000  # chain length large enough so (N-1)*1e6 = 2,999,000,000 > 2^31-1
    print(N)
    for i in range(1, N):
        print(i, i + 1, 1000000)
    print(1)
    print(1, 1, N)

if __name__ == "__main__":
    main()
