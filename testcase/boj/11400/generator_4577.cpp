#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices
    int N = rnd.next(2, 10);
    // Maximum possible edges in simple undirected graph
    int maxPossible = N * (N - 1) / 2;
    // We always add N-1 edges for a spanning tree, and up to 10 extra edges
    int maxExtra = min(maxPossible - (N - 1), 10);
    // Weighted choice of extra edges: sometimes small, sometimes large
    int tParam = (maxExtra > 0 ? rnd.next(-1, 1) : 0);
    int extra = (maxExtra > 0 ? rnd.wnext(maxExtra + 1, tParam) : 0);
    int M = (N - 1) + extra;

    // Build a random spanning tree to ensure connectivity
    vector<int> ord(N);
    iota(ord.begin(), ord.end(), 1);
    shuffle(ord.begin(), ord.end());
    vector<vector<bool>> used(N+1, vector<bool>(N+1, false));
    vector<pair<int,int>> edges;
    for (int i = 1; i < N; i++) {
        int u = ord[i];
        int v = ord[rnd.next(0, i - 1)];
        int a = min(u, v), b = max(u, v);
        edges.emplace_back(a, b);
        used[a][b] = used[b][a] = true;
    }

    // Collect candidate extra edges
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (!used[i][j]) {
                cand.emplace_back(i, j);
            }
        }
    }
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < extra; i++) {
        edges.push_back(cand[i]);
    }

    // Shuffle final edge list
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, M);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
