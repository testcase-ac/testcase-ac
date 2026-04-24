import sys

def main():
    w = sys.stdout.write
    w("1000000\n")
    # First number positive to trigger the wrong solution's branch that prints 1..1e6
    w("1\n")
    # Provide a valid set of 1,000,000 unique integers within [-1e6, 1e6]
    # We'll use the set {-499999, ..., 0, 1, 2, ..., 500000}
    # Already printed 1; now print -499999..0 (500,000 numbers)
    for x in range(-499999, 1):
        w(f"{x}\n")
    # Then print 2..500000 (499,999 numbers) to complete 1,000,000 total
    for x in range(2, 500001):
        w(f"{x}\n")

if __name__ == "__main__":
    main()
