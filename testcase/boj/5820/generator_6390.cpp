#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cities
    int N = rnd.next(2, 12);
    // Tree structure type: 0=chain, 1=star, 2=random
    int treeType = rnd.next(0, 2);
    // Maximum edge length
    int maxW = rnd.next(0, 10);
    // Bias for edge lengths: -1 -> small, 0 -> uniform, +1 -> large
    int bias = rnd.next(-1, 1);

    // Build tree edges (u, v, w)
    vector<tuple<int,int,int>> edges;
    for (int i = 1; i < N; i++) {
        int p;
        if (treeType == 0) {
            // chain
            p = i - 1;
        } else if (treeType == 1) {
            // star
            p = 0;
        } else {
            // random parent
            p = rnd.next(0, i - 1);
        }
        int w;
        if (bias < 0) {
            // bias toward smaller weights
            w = rnd.wnext(maxW + 1, -1);
        } else if (bias > 0) {
            // bias toward larger weights
            w = rnd.wnext(maxW + 1, 1);
        } else {
            // uniform
            w = rnd.next(0, maxW);
        }
        edges.emplace_back(p, i, w);
    }

    // Build adjacency to compute all path sums
    vector<vector<pair<int,int>>> adj(N);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Collect all simple path sums between u < v
    vector<int> sums;
    vector<int> dist(N);
    auto dfs = [&](auto&& self, int u, int parent) -> void {
        for (auto &pr : adj[u]) {
            int v = pr.first, w = pr.second;
            if (v == parent) continue;
            dist[v] = dist[u] + w;
            self(self, v, u);
        }
    };

    for (int s = 0; s < N; s++) {
        fill(dist.begin(), dist.end(), 0);
        dfs(dfs, s, -1);
        for (int t = s + 1; t < N; t++) {
            sums.push_back(dist[t]);
        }
    }

    // Filter non-zero sums for valid K when solution exists
    vector<int> sumsNZ;
    for (int x : sums) if (x >= 1) sumsNZ.push_back(x);

    int maxSum = sums.empty() ? 0 : *max_element(sums.begin(), sums.end());
    bool wantSol = rnd.next(0, 1) == 1;
    int K;

    if (wantSol && !sumsNZ.empty()) {
        // Pick a K that has a solution
        K = rnd.any(sumsNZ);
    } else {
        // Pick a K that likely has no solution
        int tries = 0;
        do {
            K = rnd.next(1, maxSum + 20);
            tries++;
        } while (tries < 100 && find(sums.begin(), sums.end(), K) != sums.end());
    }
    if (K < 1) K = 1;

    // Output in required format
    println(N, K);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }
    return 0;
}
