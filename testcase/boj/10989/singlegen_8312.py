# This generator produces a large valid input that forces the wrong solution's O(N^2)
# bubble sort on a linked list to time out. All numbers are valid (1..10000).
# It prints N = 100000 followed by N lines of the number 1.

import sys

def main():
    N = 100000
    out_lines = [str(N)]
    out_lines.extend(["1"] * N)
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()
