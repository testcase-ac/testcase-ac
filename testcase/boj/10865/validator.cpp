#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 1000000, "M");
    inf.readEoln();

    // Read edges and check basic constraints
    vector<pair<int,int>> edges;
    edges.reserve((size_t)M);

    for (int i = 0; i < M; i++) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readEoln();

        ensuref(a != b,
                "Self loop detected at edge index %d: (%d, %d)",
                i + 1, a, b);

        int u = min(a, b);
        int v = max(a, b);
        edges.emplace_back(u, v);
    }

    // Check for duplicate edges (undirected, so (u,v) == (v,u))
    sort(edges.begin(), edges.end());
    for (int i = 1; i < (int)edges.size(); i++) {
        if (edges[i] == edges[i - 1]) {
            ensuref(false,
                    "Multiple edges detected between nodes %d and %d",
                    edges[i].first, edges[i].second);
        }
    }

    inf.readEof();
    return 0;
}
