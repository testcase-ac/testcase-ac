import sys

def main():
    n = 100000
    out = sys.stdout
    out.write("1\n")
    out.write(f"{n}\n")
    for i in range(1, n + 1):
        out.write(f"{i} {i}\n")

if __name__ == "__main__":
    main()
