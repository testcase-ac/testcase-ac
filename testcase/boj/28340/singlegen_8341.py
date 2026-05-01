# This generator creates a single test case that causes 32-bit integer overflow in the wrong solution's accumulator
# It uses N=10000 symbols each with frequency 100000 and K=2 (binary Huffman),
# leading to an optimal total cost around 1.4e10, which exceeds 32-bit int range.

def main():
    N = 10000
    K = 2
    print(1)
    print(f"{N} {K}")
    print(" ".join(["100000"] * N))

if __name__ == "__main__":
    main()
