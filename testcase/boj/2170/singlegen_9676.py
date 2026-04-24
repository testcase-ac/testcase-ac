import sys

def main():
    # Heaviest pathological case under constraints to stress wrong solution:
    # 1,000,000 nested intervals forcing 2,000,000 unique endpoints near bounds.
    n = 1_000_000
    w = sys.stdout.write
    w(str(n) + "\n")
    left = -1_000_000_000
    right = 1_000_000_000
    # Create nested intervals: [left+i, right-i]
    for i in range(n):
        x = left + i
        y = right - i
        w(f"{x} {y}\n")

if __name__ == "__main__":
    main()
