# Layered DAG generator to force path explosion (TLE) in the wrong DFS
# Constructs a DAG with L layers, each layer has 2 nodes, fully connected to next layer.
# Number of s->e paths = 2^L, causing the wrong solution (which enumerates all paths) to time out.

def main():
    L = 30  # 2^30 paths ~ 1,073,741,824
    n = 2 * L + 2  # start + 2 nodes per layer + end
    m = 4 * L      # 2 edges from start, 4 per intermediate layer, 2 into end

    print(n)
    print(m)

    # Node numbering:
    # 1 = start, 2..(2L+1) are layers (pairs), 2L+2 = end
    start = 1
    end = n

    # From start to first layer (nodes 2 and 3)
    print(start, 2, 1)
    print(start, 3, 1)

    # Between layers: for i in [1..L-1], connect layer i to layer i+1 fully (2x2=4 edges)
    for i in range(1, L):
        Ai = 2 + 2 * (i - 1)
        Bi = Ai + 1
        Aj = 2 + 2 * i
        Bj = Aj + 1
        for u in (Ai, Bi):
            for v in (Aj, Bj):
                print(u, v, 1)

    # Last layer to end
    AL = 2 + 2 * (L - 1)
    BL = AL + 1
    print(AL, end, 1)
    print(BL, end, 1)

    # Start and end
    print(start, end)

if __name__ == "__main__":
    main()
