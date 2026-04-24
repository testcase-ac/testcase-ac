#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checking
    int N = rnd.next(3, 10);

    // Hyper-parameter: tree shape
    int shape = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (shape == 0) {
        // Random tree: attach i to random [1..i-1]
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(p, i);
        }
    } else if (shape == 1) {
        // Line tree, possibly shuffled
        vector<int> seq(N);
        for (int i = 0; i < N; i++) seq[i] = i + 1;
        if (rnd.next(0, 1)) shuffle(seq.begin(), seq.end());
        for (int i = 1; i < N; i++) {
            edges.emplace_back(seq[i - 1], seq[i]);
        }
    } else {
        // Star tree
        int center = rnd.next(1, N);
        for (int v = 1; v <= N; v++) {
            if (v == center) continue;
            edges.emplace_back(center, v);
        }
    }

    // Hyper-parameter: weight max and bias
    int Wmax = rnd.next(5, 20);
    int tW = rnd.next(-1, 1); // bias for wnext

    // Assign weights
    vector<tuple<int,int,int>> we;
    for (auto &e : edges) {
        int w = rnd.wnext(Wmax, tW) + 1;
        we.emplace_back(e.first, e.second, w);
    }

    // Hyper-parameter: permute node labels
    if (rnd.next(0, 1)) {
        vector<int> p(N + 1);
        for (int i = 1; i <= N; i++) p[i] = i;
        shuffle(p.begin() + 1, p.end());
        for (auto &t : we) {
            int u, v, w;
            tie(u, v, w) = t;
            u = p[u];
            v = p[v];
            t = make_tuple(u, v, w);
        }
    }

    // Build adjacency
    vector<vector<pair<int,int>>> adj(N + 1);
    for (auto &t : we) {
        int u, v, w;
        tie(u, v, w) = t;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // Compute all-pairs distances by DFS from each node
    vector<vector<int>> dist(N + 1, vector<int>(N + 1, 0));
    auto dfs = [&](auto&& self, int src, int u, int p, int d) -> void {
        dist[src][u] = d;
        for (auto &pr : adj[u]) {
            int v = pr.first, w = pr.second;
            if (v == p) continue;
            self(self, src, v, u, d + w);
        }
    };
    for (int i = 1; i <= N; i++) {
        dfs(dfs, i, i, 0, 0);
    }

    // Output in Floyd-style upper triangle
    println(N);
    for (int i = 1; i <= N - 1; i++) {
        vector<int> line;
        for (int j = i + 1; j <= N; j++) {
            line.push_back(dist[i][j]);
        }
        println(line);
    }

    return 0;
}
