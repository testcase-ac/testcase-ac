import sys

def main():
    n = 5_000_000
    L = 1
    out = sys.stdout
    out.write(f"{n} {L}\n")
    # Worst-case for the segment tree approach: tiny window every time.
    # Output n integers (all zeros) efficiently in chunks without extra spaces at the end.
    tokens_to_space = n - 1
    block = 1_000_000
    full_blocks = tokens_to_space // block
    rem = tokens_to_space % block
    chunk = ("0 " * block)
    for _ in range(full_blocks):
        out.write(chunk)
    if rem:
        out.write("0 " * rem)
    out.write("0\n")

if __name__ == "__main__":
    main()
