#include "testlib.h"
#include <unordered_set>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(3, 500000, "n");
    inf.readSpace();
    int m = inf.readInt(3, 1000000, "m");
    inf.readEoln();

    // We will check no loops and no duplicate edges.
    // Use a hash set of packed pairs (min<<32 | max).
    unordered_set<uint64_t> seen;
    seen.reserve((size_t)m * 2);

    for (int i = 1; i <= m; i++) {
        int u = inf.readInt(0, n-1, "u_i");
        inf.readSpace();
        int v = inf.readInt(0, n-1, "v_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected at move %d: endpoints are equal (%d, %d)",
                i, u, v);
        // Normalize edge
        int a = min(u, v), b = max(u, v);
        uint64_t key = (uint64_t(a) << 32) | uint64_t(b);
        ensuref(!seen.count(key),
                "Duplicate edge detected at move %d: (%d, %d)",
                i, a, b);
        seen.insert(key);
    }

    inf.readEof();
    return 0;
}
