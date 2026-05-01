import sys

def main():
    n = 100000
    a = " ".join(map(str, range(1, n + 1)))
    b = " ".join(map(str, range(n, 0, -1)))
    sys.stdout.write(str(n) + "\n")
    sys.stdout.write(a + "\n")
    sys.stdout.write(b + "\n")

if __name__ == "__main__":
    main()
