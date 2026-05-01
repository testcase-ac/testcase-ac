# Generates a worst-case test where the wrong solution times out due to O(N^2) string operations
# N = 100000, single ENTER, then 99999 unique long nicknames (length 20)

def main():
    N = 100000
    print(N)
    print("ENTER")
    for i in range(N - 1):
        # Create a 20-character nickname consisting of letters/digits only
        # e.g., "aaaaaaaaaaaaaaa00000", "aaaaaaaaaaaaaaa00001", ...
        s = "a" * (20 - len(str(i))) + str(i)
        print(s)

if __name__ == "__main__":
    main()
