import sys

def main():
    # This test triggers 32-bit integer overflow in the wrong solution's sum accumulator (int t)
    # N = 100000, all expected ranks are 100000
    # Minimal dissatisfaction = sum_{i=1..N} |100000 - i| = 4,999,950,000 > 2^31-1
    n = 100000
    out = [str(n)]
    out.extend(["100000"] * n)
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    main()
