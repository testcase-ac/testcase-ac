import sys

def main():
    N = 27  # multi-digit to break the buggy readInt that only reads one digit
    print(N)
    row = ' '.join(['0'] * N)
    for _ in range(N):
        print(row)

if __name__ == "__main__":
    main()
