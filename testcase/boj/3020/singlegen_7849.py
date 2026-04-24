import sys

def main():
    N = 200000
    H = 500000
    w = sys.stdout.write
    w(f"{N} {H}\n")
    line = f"{H-1}\n"
    for _ in range(N):
        w(line)

if __name__ == "__main__":
    main()
