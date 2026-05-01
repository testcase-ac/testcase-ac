# This generator creates a 200x200 campus with I at (0,0) and all other cells as P.
# The correct reachable people count is 200*200 - 1 = 39999.
# The wrong solution uses `short` for the counter, which overflows (16-bit),
# resulting in an incorrect negative value.

def main():
    n, m = 200, 200
    print(f"{n} {m}")
    # First row: I followed by P's
    print("I" + "P" * (m - 1))
    # Remaining rows: all P's
    row = "P" * m
    for _ in range(n - 1):
        print(row)

if __name__ == "__main__":
    main()
