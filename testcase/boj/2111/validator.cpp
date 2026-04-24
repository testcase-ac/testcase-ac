#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 20000, "N");
    inf.readSpace();
    int M = inf.readInt(0, 1000, "M");
    inf.readEoln();

    long long edge_count = 0;
    set<pair<int,int>> edges;

    for (int i = 0; i < M; i++) {
        // Read path length L_i: at least 1, at most N+1 (simple path or simple cycle)
        int L = inf.readInt(1, N + 1, "path_length");
        vector<int> p;
        p.reserve(L);
        // Read the L vertex indices, each in [1, N]
        for (int j = 0; j < L; j++) {
            inf.readSpace();
            int v = inf.readInt(1, N, "path_vertex");
            p.push_back(v);
        }
        inf.readEoln();

        // Build edges from consecutive vertices
        for (int j = 0; j + 1 < L; j++) {
            int u = p[j];
            int v = p[j+1];
            // No self-loop
            ensuref(u != v,
                    "Self-loop detected in path %d at positions %d and %d: (%d,%d)",
                    i+1, j+1, j+2, u, v);
            // Normalize undirected edge
            int a = min(u, v);
            int b = max(u, v);
            pair<int,int> e = make_pair(a, b);
            // No duplicate edges
            ensuref(!edges.count(e),
                    "Multiple occurrence of edge (%d,%d) in path %d at positions %d-%d",
                    u, v, i+1, j+1, j+2);
            edges.insert(e);
            edge_count++;
        }
    }

    // Total edges ≤ 2N
    ensuref(edge_count <= 2LL * N,
            "Too many edges: %lld edges but at most 2*%d allowed",
            edge_count, N);

    inf.readEof();
    return 0;
}
