#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of people
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Adjacency lists (1-based)
    vector<vector<int>> adj(N+1);
    long long undirectedEdges = 0;

    for (int i = 1; i <= N; i++) {
        // Read neighbors until 0
        unordered_set<int> seen;
        while (true) {
            int v = inf.readInt(0, N, "neighbor");
            if (v == 0) {
                break;
            }
            // Validate neighbor
            ensuref(v != i,
                    "Self loop detected: person %d lists itself as neighbor", i);
            ensuref(seen.insert(v).second,
                    "Duplicate neighbor %d in list of person %d", v, i);
            adj[i].push_back(v);
            inf.readSpace();
        }
        inf.readEoln();
    }

    // Sort and check local duplicates (just in case)
    for (int i = 1; i <= N; i++) {
        auto &vec = adj[i];
        sort(vec.begin(), vec.end());
        for (int j = 1; j < (int)vec.size(); j++) {
            ensuref(vec[j] != vec[j-1],
                    "Duplicate neighbor %d in list of person %d after sort", vec[j], i);
        }
    }

    // Check symmetry and count undirected edges
    for (int i = 1; i <= N; i++) {
        for (int v : adj[i]) {
            // Symmetric check: v's list must contain i
            bool found = binary_search(adj[v].begin(), adj[v].end(), i);
            ensuref(found,
                    "Asymmetric relationship: person %d lists %d but not vice versa", i, v);
            if (i < v) {
                undirectedEdges++;
            }
        }
    }
    ensuref(undirectedEdges <= 1000000LL,
            "Total undirected edges %lld exceeds limit 1000000", undirectedEdges);

    // Initial spreaders
    int M = inf.readInt(1, N, "M");
    inf.readEoln();
    vector<int> init = inf.readInts(M, 1, N, "initial");
    // Check distinctness
    {
        auto tmp = init;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < M; i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate initial spreader %d", tmp[i]);
        }
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
