#include "testlib.h"
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N
    int N = rnd.next(2, 10);

    // Build a random tree by connecting each i to a random previous node
    vector<tuple<int,int,int>> edges;
    for (int i = 2; i <= N; i++) {
        int p = rnd.next(1, i - 1);
        // Hyper-parameter for edge weight skew
        vector<int> wts = {-3, -1, 0, 1, 3};
        int tW = rnd.any(wts);
        int w = rnd.wnext(20, tW) + 1;  // weights in [1..21]
        edges.emplace_back(p, i, w);
    }

    // Build adjacency for path finding
    vector<vector<pair<int,int>>> adj(N+1);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // Hyper-parameter for number of queries
    vector<int> tMs = {-2, 0, 2};
    int tM = rnd.any(tMs);
    int M = rnd.wnext(20, tM) + 1;  // M in [1..21]

    // Hyper-parameter for query type distribution
    vector<double> prList = {0.2, 0.5, 0.8};
    double pType1 = rnd.any(prList);

    // Output tree
    println(N);
    for (auto &e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        println(u, v, w);
    }

    // Function to find path from u to v
    function<bool(int,int,int,vector<int>&)> dfs = [&](int cur, int target, int parent, vector<int> &path) {
        if (cur == target) {
            path.push_back(cur);
            return true;
        }
        for (auto &nx : adj[cur]) {
            int to = nx.first;
            if (to == parent) continue;
            if (dfs(to, target, cur, path)) {
                path.push_back(cur);
                return true;
            }
        }
        return false;
    };

    // Generate queries
    println(M);
    for (int i = 0; i < M; i++) {
        bool isType1 = rnd.next() < pType1;
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        if (isType1) {
            // Query type 1: path cost
            println(1, u, v);
        } else {
            // Query type 2: k-th vertex on path
            vector<int> path;
            dfs(u, v, -1, path);
            reverse(path.begin(), path.end());
            int K = rnd.next(1, (int)path.size());
            println(2, u, v, K);
        }
    }

    return 0;
}
