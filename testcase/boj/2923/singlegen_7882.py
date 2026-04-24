# Generates a test where the wrong solution fails due to using a stopping condition Ac < 100.
# After 100 occurrences of the smallest A value, it outputs 0 instead of the correct value.

def main():
    N = 100
    print(N)
    for _ in range(N):
        # Keep both A and B as 1, so the correct answer is always 2.
        print("1 1")

if __name__ == "__main__":
    main()
