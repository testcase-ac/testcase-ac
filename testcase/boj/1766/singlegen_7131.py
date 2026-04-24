# This generator creates a DAG where node 1 has more than 999 outgoing edges.
# The wrong solution stores adjacency with fixed width 1000 and 1-based indexing on the second dimension,
# leading to out-of-bounds access when a node has >= 1000 outgoing edges.
# This test will therefore cause incorrect behavior (WA/RE).

def main():
    N = 2001
    M = 2000
    print(f"{N} {M}")
    for i in range(2, N + 1):
        print(f"1 {i}")

if __name__ == "__main__":
    main()
