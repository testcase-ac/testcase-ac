#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2000000, "m");
    inf.readEoln();

    // Read edges, check for self-loops, collect for duplicate detection
    vector<unsigned long long> edges;
    edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();
        ensuref(u != v,
                "Self-loop detected at edge index %d: (%d, %d)",
                i, u, v);
        int a = min(u, v), b = max(u, v);
        unsigned long long code = ( (unsigned long long)a << 32 ) | (unsigned int)b;
        edges.push_back(code);
    }

    // Check for multiple edges (undirected, so (a,b) same as (b,a))
    sort(edges.begin(), edges.end());
    for (int i = 1; i < (int)edges.size(); i++) {
        ensuref(edges[i] != edges[i-1],
                "Multiple edges detected between students %u and %u",
                (unsigned int)(edges[i] >> 32),
                (unsigned int)(edges[i] & 0xFFFFFFFF));
    }

    inf.readEof();
    return 0;
}
