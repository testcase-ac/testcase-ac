# This generator creates many parallel edges from the start node to every other node
# to force the wrong solution to push the same vertex multiple times (one per improved edge),
# exceeding its heap capacity of 20001.
#
# Specifically, for N=2002, we add 10 parallel edges (weights 1..10) from node 1 to each node v>=2.
# When processing node 1, the wrong solution will encounter, for each v, edges in order 10..1 (due to
# head insertion), causing 10 pushes per vertex. Total pushes: 10*(N-1) + 1 = 20011 > 20001,
# which overflows the heap array and leads to a non-AC verdict.

def main():
    N = 2002
    M = 10 * (N - 1)
    print(f"{N} {M}")
    print(1)
    for v in range(2, N + 1):
        for w in range(1, 11):
            print(f"1 {v} {w}")

if __name__ == "__main__":
    main()
