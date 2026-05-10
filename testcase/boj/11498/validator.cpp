#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N and M
        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int M = inf.readInt(0, 1000000, "M");
        inf.readEoln();

        // Read all edges and check loops; store for duplicate detection
        vector<uint64_t> edges;
        edges.reserve(M);

        for (int i = 0; i < M; ++i) {
            int v = inf.readInt(1, N, "v");
            inf.readSpace();
            int w = inf.readInt(1, N, "w");
            inf.readEoln();

            // No self‐loops allowed
            ensuref(v != w,
                    "Self-loop detected at edge %d in test case %d: (%d -> %d)",
                    i+1, tc, v, w);

            // Pack into 64-bit for sorting
            uint64_t key = (uint64_t(v) << 32) | uint32_t(w);
            edges.push_back(key);
        }

        // Check for multiple edges by sorting and scanning
        sort(edges.begin(), edges.end());
        for (int i = 1; i < (int)edges.size(); ++i) {
            if (edges[i] == edges[i-1]) {
                uint32_t v = edges[i] >> 32;
                uint32_t w = edges[i] & 0xFFFFFFFFu;
                ensuref(false,
                        "Multiple edges detected in test case %d: (%u -> %u)",
                        tc, v, w);
            }
        }
    }

    inf.readEof();
    return 0;
}
