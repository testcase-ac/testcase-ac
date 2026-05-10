#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 300000, "M");
    inf.readEoln();

    // Read edges, check basic constraints
    vector<pair<int,int>> edges;
    edges.reserve(M);
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();
        ensuref(u != v,
                "Self loop detected at edge %d: (%d, %d)",
                i+1, u, v);
        // store in normalized order
        if (u > v) swap(u, v);
        edges.emplace_back(u, v);
    }

    // Check no duplicate edges
    sort(edges.begin(), edges.end());
    for (int i = 1; i < M; i++) {
        if (edges[i] == edges[i-1]) {
            int u = edges[i].first;
            int v = edges[i].second;
            ensuref(false,
                    "Multiple edges detected between nodes %d and %d",
                    u, v);
        }
    }

    // Check planar graph necessary condition:
    // For N >= 3: M <= 3N - 6
    // For N == 2: M <= 1
    // For N == 1: M == 0
    long long maxEdges;
    if (N >= 3) {
        maxEdges = 3LL * N - 6LL;
    } else if (N == 2) {
        maxEdges = 1;
    } else { // N == 1
        maxEdges = 0;
    }
    ensuref((long long)M <= maxEdges,
            "Graph is not planar: M = %d exceeds the planar limit %lld for N = %d",
            M, maxEdges, N);

    inf.readEof();
    return 0;
}
