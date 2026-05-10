#include "testlib.h"
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, M, R
    int N = inf.readInt(5, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int R = inf.readInt(1, N, "R");
    inf.readEoln();

    // Read M edges and validate
    unordered_set<long long> edges;
    edges.reserve((size_t)M * 2);
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No self-loops, enforce u < v
        ensuref(u < v,
                "Edge %d is invalid: expected u < v, found u=%d, v=%d",
                i+1, u, v);

        long long key = ( (long long)u << 32 ) | (unsigned long long)v;
        ensuref(!edges.count(key),
                "Multiple edges detected at edge %d: (%d, %d)",
                i+1, u, v);

        edges.insert(key);
    }

    inf.readEof();
    return 0;
}
