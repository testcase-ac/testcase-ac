# Generate a single test case with maximum K = 1,000,000 files,
# each of the largest allowed size 10000.
# This stresses both input size and the merging algorithm.
import sys

def main():
    N = 10**6
    sys.stdout.write("1\n")        # T = 1
    sys.stdout.write(f"{N}\n")     # K = 1,000,000
    # All file sizes = 10000
    # Use join for efficient one‐shot output
    sys.stdout.write(" ".join(["10000"] * N))

if __name__ == "__main__":
    main()
