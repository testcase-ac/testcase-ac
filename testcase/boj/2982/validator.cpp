#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 10000, "M");
    inf.readEoln();

    // Read A, B, K, G
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readSpace();
    int K = inf.readInt(0, 1000, "K");
    inf.readSpace();
    int G = inf.readInt(0, 1000, "G");
    inf.readEoln();

    // Read the king's visited intersections
    vector<int> path;
    if (G > 0) {
        path = inf.readInts(G, 1, N, "path");
    }
    inf.readEoln();

    // Read the roads
    // We will store for each undirected pair the list of edge indices
    map<pair<int,int>, vector<int>> edge_map;
    edge_map.clear();
    for (int i = 0; i < M; i++) {
        int U = inf.readInt(1, N, "U");
        inf.readSpace();
        int V = inf.readInt(1, N, "V");
        inf.readSpace();
        int L = inf.readInt(1, 1000, "L");
        inf.readEoln();

        int x = min(U, V);
        int y = max(U, V);
        edge_map[{x, y}].push_back(i);
    }

    // Validate the king's path:
    // 1) For each consecutive pair, there must be at least one road
    // 2) No road (by endpoints) is used more than once
    set<pair<int,int>> used;
    for (int i = 0; i + 1 < G; i++) {
        int u = path[i];
        int v = path[i+1];
        int x = min(u, v);
        int y = max(u, v);
        auto it = edge_map.find({x, y});
        ensuref(it != edge_map.end(),
                "No road exists between path[%d]=%d and path[%d]=%d", 
                i, u, i+1, v);
        ensuref(!used.count({x, y}),
                "Road between nodes %d and %d is used more than once in the king's path at index %d",
                u, v, i);
        used.insert({x, y});
    }

    inf.readEof();
    return 0;
}
