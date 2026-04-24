# This generator creates a case that causes 32-bit integer overflow in the wrong solution's sum.
# N is set so that the total required supervisors exceeds Integer.MAX_VALUE.
# Each exam hall has 1,000,000 students, B=1, C=1, so each hall needs exactly 1,000,000 supervisors.
# With N=2148, total = 2,148,000,000 > 2,147,483,647, causing overflow in the wrong Java code.

def main():
    N = 2148
    print(N)
    print(" ".join(["1000000"] * N))
    print("1 1")

if __name__ == "__main__":
    main()
