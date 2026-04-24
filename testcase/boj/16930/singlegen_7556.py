# This generator creates a maximal-size grid (1000x1000) with K=1000,
# filled with empty cells, start at (1,1) and end at (1000,1000).
# The wrong solution accesses the grid before bounds-checking when stepping up/left,
# causing out-of-bounds reads and likely a crash on this input.

def main():
    n = 1000
    m = 1000
    k = 1000
    print(f"{n} {m} {k}")
    row = "." * m
    for _ in range(n):
        print(row)
    print("1 1 1000 1000")

if __name__ == "__main__":
    main()
