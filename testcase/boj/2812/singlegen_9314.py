# Generates a test that causes buffer overflow in the wrong solution due to tiny fixed arrays (size 54)
# compared to problem constraints (N up to 500000). This should lead to RE or incorrect output.

def main():
    n = 500000
    k = 499999
    print(f"{n} {k}")
    print("9" * n)

if __name__ == "__main__":
    main()
