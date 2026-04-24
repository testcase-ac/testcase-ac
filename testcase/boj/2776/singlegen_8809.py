import sys

def main():
    # Construct a worst-case input for the given solution:
    # - Uses std::map for both the note1 set and the outputs, leading to heavy O(log N) per op
    # - Uses slow iostream without sync optimizations
    # - Maximal sizes to induce TLE (and heavy memory use)
    T = 1
    N = 1_000_000
    M = 1_000_000

    out = sys.stdout
    out.write(str(T) + "\n")
    out.write(str(N) + "\n")
    # Note1: 1..N
    out.write(" ".join(map(str, range(1, N + 1))) + "\n")
    out.write(str(M) + "\n")
    # Note2: 1..M (all hits)
    out.write(" ".join(map(str, range(1, M + 1))) + "\n")

if __name__ == "__main__":
    main()
