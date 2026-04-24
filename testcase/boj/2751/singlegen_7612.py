import sys

def main():
    n = 1000000
    out = sys.stdout
    out.write(str(n) + "\n")
    # Provide numbers 0..999999. The wrong solution with n==1e6 reads only the first number (0)
    # and then prints 1..1000000, which mismatches the correct sorted output 0..999999.
    for i in range(n):
        out.write(str(i) + "\n")

if __name__ == "__main__":
    main()
