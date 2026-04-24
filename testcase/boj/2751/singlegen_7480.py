import sys

def main():
    N = 1_000_000
    out = sys.stdout
    out.write(str(N) + "\n")
    # Provide N distinct integers within [-1_000_000, 1_000_000], not equal to 1..N
    # This triggers the wrong solution's hardcoded branch for N==1_000_000,
    # which incorrectly prints 1..N regardless of input values.
    for x in range(-1_000_000, 0):
        out.write(str(x) + "\n")

if __name__ == "__main__":
    main()
