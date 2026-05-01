# This generator creates many large test cases to trigger TLE in the naive primality check.
# It prints the maximum n (123456) multiple times, followed by a terminating 0.

def main():
    T = 300  # number of heavy test cases
    for _ in range(T):
        print(123456)
    print(0)

if __name__ == "__main__":
    main()
