# Generates a worst-case chain tree with maximum-distance queries to force TLE/stack overflow
# for the given wrong solution (per-query path traversal O(distance)).
# N = 100000, K = 100000, edges form a chain, all queries are (1, N).

def main():
    import sys
    N = 100000
    K = 100000
    out = []
    out.append(str(N))
    # Chain edges with weight 1
    for i in range(1, N):
        out.append(f"{i} {i+1} 1")
    out.append(str(K))
    q = f"1 {N}"
    out.extend([q] * K)
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    main()
