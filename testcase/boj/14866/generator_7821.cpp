#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: mix small/medium/large within [3,12]
    vector<int> t1 = {-2, 0, 2};
    int rawN = rnd.wnext(10, rnd.any(t1)); // 0..9 skewed
    int N = rawN + 3; // 3..12
    // Build a random spanning tree to ensure connectivity
    vector<pair<int,int>> edges;
    for (int i = 2; i <= N; ++i) {
        int p = rnd.next(1, i - 1);
        edges.emplace_back(p, i);
    }
    // Collect candidate extra edges (no multi-edge, undirected)
    vector<vector<bool>> adj(N+1, vector<bool>(N+1, false));
    for (auto &e : edges) {
        adj[e.first][e.second] = adj[e.second][e.first] = true;
    }
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (!adj[i][j]) cand.emplace_back(i, j);
        }
    }
    // Choose number of extra edges K: at least 1, at most min(N, cand.size())
    int maxExtra = min((int)cand.size(), N);
    vector<int> t2 = {-1, 1};
    int rawK = rnd.wnext(maxExtra + 1, rnd.any(t2)); // 0..maxExtra
    int K = rawK == 0 ? 1 : rawK;
    // Sample K extras
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < K; ++i) edges.push_back(cand[i]);
    // Shuffle all edges to diversify order
    shuffle(edges.begin(), edges.end());
    int M = edges.size();
    // Output
    println(N, M);
    for (auto &e : edges) println(e.first, e.second);
    return 0;
}
