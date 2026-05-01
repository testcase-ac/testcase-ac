import sys

def name_from_index(i: int) -> str:
    # Generate a 5-letter uppercase name based on base-26 encoding
    chars = []
    for _ in range(5):
        chars.append(chr(ord('A') + (i % 26)))
        i //= 26
    return ''.join(chars)


def main():
    # Construct a large valid log that forces many costly list.remove operations
    # Pattern: N enters (unique names), then N leaves in reverse order
    # This keeps the log consistent and valid, but removal cost is O(N^2).
    N = 120000  # Total lines will be 2*N = 240000
    w = sys.stdout.write
    w(str(2 * N) + "\n")
    for i in range(N):
        w(name_from_index(i) + " enter\n")
    for i in range(N - 1, -1, -1):
        w(name_from_index(i) + " leave\n")


if __name__ == "__main__":
    main()
