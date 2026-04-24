import sys

def write_range(start, end):
    out = sys.stdout
    chunk_size = 50000
    i = start
    remaining = end - start + 1
    first = True
    while remaining > 0:
        k = min(chunk_size, remaining)
        s = ' '.join(map(str, range(i, i + k)))
        if first:
            out.write(s)
            first = False
        else:
            out.write(' ' + s)
        remaining -= k
        i += k
    out.write('\n')


def main():
    out = sys.stdout
    T = 3
    out.write(f"{T}\n")
    N = 1_000_000
    M = 1_000_000
    for t in range(T):
        out.write(f"{N}\n")
        # Notebook 1: 1..N
        write_range(1, N)
        out.write(f"{M}\n")
        # Notebook 2: disjoint queries to force map[a] insertions (worst-case for std::map)
        base = (t + 1) * (N + M) + 1
        write_range(base, base + M - 1)


if __name__ == "__main__":
    main()
