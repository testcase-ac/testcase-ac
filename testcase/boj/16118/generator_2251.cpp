#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for small test case
    int N = rnd.next(2, 9);                        // number of nodes between 2 and 9
    double density = rnd.next(0.2, 1.0);           // fraction of possible edges to include
    int maxW = rnd.next(5, 20);                    // maximum edge weight between 5 and 20

    // Build all possible undirected edges (i < j)
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            allEdges.emplace_back(i, j);
        }
    }

    // Shuffle and pick M edges based on density
    shuffle(allEdges.begin(), allEdges.end());
    int maxPossible = (int)allEdges.size();
    int M = rnd.next(1, maxPossible);
    // Force approximate density
    M = max(1, min(maxPossible, (int)(density * maxPossible + rnd.next(-1,1))));
    
    // Output N, M
    println(N, M);

    // Assign random weights and print edges
    for (int i = 0; i < M; i++) {
        int u = allEdges[i].first;
        int v = allEdges[i].second;
        int d = rnd.next(1, maxW);
        println(u, v, d);
    }

    return 0;
}
