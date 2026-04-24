#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes
    int N = rnd.next(2, 10);

    // Hyper-parameter: choose a maximum weight from typical scales
    vector<int> weightScales = {1, 10, 100, 1000, 10000};
    int maxW = rnd.any(weightScales);

    // Hyper-parameter: bias for weight distribution
    // Positive => heavier edges more likely, negative => lighter edges more likely
    int weightBias = rnd.next(-2, 2);

    // 1) Build a random spanning tree to ensure connectivity
    vector<tuple<int,int,int>> edges;
    for (int v = 2; v <= N; v++) {
        int u = rnd.next(1, v - 1);
        int w = rnd.wnext(maxW, weightBias) + 1;
        edges.emplace_back(u, v, w);
    }

    // 2) Prepare all possible non-tree edges (u < v, not in tree)
    vector<pair<int,int>> candidates;
    vector<vector<bool>> inTree(N+1, vector<bool>(N+1, false));
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        inTree[u][v] = inTree[v][u] = true;
    }
    for (int u = 1; u <= N; u++) {
        for (int v = u + 1; v <= N; v++) {
            if (!inTree[u][v]) candidates.emplace_back(u, v);
        }
    }

    // 3) Add some extra edges, up to N-1 more
    shuffle(candidates.begin(), candidates.end());
    int maxExtra = min((int)candidates.size(), N - 1);
    int E = rnd.next(0, maxExtra);
    for (int i = 0; i < E; i++) {
        int u = candidates[i].first;
        int v = candidates[i].second;
        int w = rnd.wnext(maxW, weightBias) + 1;
        edges.emplace_back(u, v, w);
    }

    // 4) Add a few self-loops (allowed by problem, but irrelevant to MST)
    int L = rnd.next(0, min(N, 2));
    for (int i = 0; i < L; i++) {
        int u = rnd.next(1, N);
        int w = rnd.wnext(maxW, weightBias) + 1;
        edges.emplace_back(u, u, w);
    }

    // 5) Shuffle all edges to avoid any ordering
    shuffle(edges.begin(), edges.end());

    // Output
    int M = edges.size();
    println(N);
    println(M);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }

    return 0;
}
