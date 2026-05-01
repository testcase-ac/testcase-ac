import sys

def main():
    n = 300000
    sys.stdout.write(str(n) + "\n")
    # All ratings are the same; this still forces O(n^2) behavior due to repeated del level[0]
    sys.stdout.write(("1\n") * n)

if __name__ == "__main__":
    main()
