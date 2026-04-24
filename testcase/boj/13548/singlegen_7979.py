# This generator creates a worst-case scenario for the given (buggy) Mo's algorithm implementation.
# The comparator in the wrong solution incorrectly uses the parity of l (l&1) instead of block parity,
# which can lead to highly non-local query ordering and potentially TLE due to excessive pointer movement.
# We generate many queries within the same left block with r swinging between very small and very large values.

import sys

def main():
    N = 100000
    # Array values: strictly increasing (content doesn't matter for performance stress)
    A = list(range(1, N+1))

    # Number of queries
    M = 100000

    # Choose K as int(sqrt(N)) ~ 316 to match the wrong solution's block size
    # Put all l within the first block [1..K]
    import math
    K = int(math.isqrt(N))

    out_lines = []
    out_lines.append(str(N))
    out_lines.append(" ".join(map(str, A)))
    out_lines.append(str(M))

    # Construct queries alternating r between very small (l) and very large (N).
    # l cycles through [1..K], so all queries belong to the same l-block.
    for t in range(1, M+1):
        l = (t-1) % K + 1
        if t % 2 == 1:
            r = N
        else:
            r = l
        out_lines.append(f"{l} {r}")

    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()
