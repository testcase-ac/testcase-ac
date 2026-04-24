#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of areas N
    int N = inf.readInt(2, 10, "N");
    inf.readEoln();

    // Read populations
    vector<int> population = inf.readInts(N, 1, 100, "population");
    inf.readEoln();

    // Read adjacency lists
    // adj[i] will store neighbors of node i (1-indexed)
    vector<vector<int>> adj(N+1);
    for (int i = 1; i <= N; i++) {
        // number of neighbors
        string cnt_name = "adj_count[" + to_string(i) + "]";
        int k = inf.readInt(0, N-1, cnt_name.c_str());
        // neighbors
        set<int> seen;
        for (int j = 0; j < k; j++) {
            inf.readSpace();
            string nei_name = "adjacent[" + to_string(i) + "][" + to_string(j) + "]";
            int v = inf.readInt(1, N, nei_name.c_str());
            // no self-loop
            ensuref(v != i,
                    "Self-loop detected at node %d -> %d", i, v);
            // no duplicates
            ensuref(!seen.count(v),
                    "Duplicate adjacency detected at node %d -> %d", i, v);
            seen.insert(v);
            adj[i].push_back(v);
        }
        inf.readEoln();
    }

    // Check symmetry: if i lists v, then v must list i
    for (int i = 1; i <= N; i++) {
        for (int v : adj[i]) {
            bool found = false;
            for (int u : adj[v]) {
                if (u == i) {
                    found = true;
                    break;
                }
            }
            ensuref(found,
                    "Asymmetric adjacency: %d lists %d but not vice versa", i, v);
        }
    }

    inf.readEof();
    return 0;
}
