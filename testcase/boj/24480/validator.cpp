#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 5;
    const int N_MAX = 100000;
    const int M_MIN = 1;
    const int M_MAX = 200000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(M_MIN, M_MAX, "M");
    inf.readSpace();
    int R = inf.readInt(1, N, "R");
    inf.readEoln();

    // read edges, check constraints and no duplicates
    set<pair<int,int>> edges;
    vector<vector<int>> adj(N + 1);

    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        // problem states 1 ≤ u < v ≤ N, u ≠ v
        ensuref(u < v, "Edge %d must satisfy 1 <= u < v <= N, but got u=%d, v=%d", i + 1, u, v);

        pair<int,int> e = {u, v};
        ensuref(!edges.count(e), "Multiple edges detected at index %d: (%d, %d)", i + 1, u, v);
        edges.insert(e);

        // undirected graph adjacency
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // No extra lines after the last edge line
    inf.readEof();

    // The statement guarantees all edges have weight 1 (implicit, not in input).
    // Global property checks:
    // - None about connectivity, answer existence, etc., beyond basic graph validity.
    // However, ensure graph structure is non-degenerate:
    //   (No loops and no multi-edges already enforced; simple graph.)

    // We do NOT check DFS order or reachability constraints since they are for the solution.

    return 0;
}
