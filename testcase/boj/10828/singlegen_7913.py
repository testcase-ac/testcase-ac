# Generate a test that exceeds the fixed stack capacity (100) but stays within N <= 10000
# We push 9999 items, then issue one 'top' to force the program to read far beyond its array.

def main():
    n_push = 9999
    print(n_push + 1)
    for i in range(1, n_push + 1):
        print(f"push {i}")
    print("top")

if __name__ == "__main__":
    main()
