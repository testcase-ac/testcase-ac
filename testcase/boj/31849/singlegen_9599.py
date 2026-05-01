import sys

def main():
    N, M = 1000, 1000
    R, C = 499_999, 1  # R + C = 500000 (max per constraints)
    out = []
    out.append(f"{N} {M} {R} {C}\n")

    # Place the single convenience store at (1,1)
    store_x, store_y = 1, 1

    # Generate R rooms starting from the farthest cells from (1,1)
    # This maximizes the BFS work for the wrong solution (per-room BFS)
    cnt = 0
    for i in range(N, 0, -1):
        for j in range(M, 0, -1):
            if i == store_x and j == store_y:
                continue
            out.append(f"{i} {j} 1\n")  # rent = 1 (any valid value works)
            cnt += 1
            if cnt == R:
                break
        if cnt == R:
            break

    # Convenience store
    out.append(f"{store_x} {store_y}\n")

    sys.stdout.write(''.join(out))

if __name__ == "__main__":
    main()
