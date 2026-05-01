#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of nodes and queries
    int N = rnd.next(2, 10);
    int M = rnd.next(1, 20);

    // Generate distinct weights 1..N, shuffled, with random signs
    vector<int> w(N);
    for (int i = 0; i < N; i++) w[i] = i + 1;
    shuffle(w.begin(), w.end());
    for (int i = 0; i < N; i++) {
        if (rnd.next(0, 1) == 0) w[i] = -w[i];
    }

    // Choose tree shape: 0=random, 1=line, 2=star
    int treeType = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (treeType == 0) {
        // random tree via random parent
        for (int v = 2; v <= N; v++) {
            int p = rnd.next(1, v - 1);
            edges.emplace_back(p, v);
        }
    } else if (treeType == 1) {
        // line tree 1-2-3-...
        for (int v = 2; v <= N; v++) {
            edges.emplace_back(v - 1, v);
        }
    } else {
        // star centered at 1
        for (int v = 2; v <= N; v++) {
            edges.emplace_back(1, v);
        }
    }

    // Build adjacency for path queries
    vector<vector<int>> adj(N + 1);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    // Shuffle edge output order
    shuffle(edges.begin(), edges.end());

    // Generate queries ensuring K is valid
    vector<tuple<int,int,int>> qs;
    for (int i = 0; i < M; i++) {
        int x = rnd.next(1, N);
        int y = rnd.next(1, N);
        // BFS to find path from x to y
        vector<int> par(N + 1, -1);
        queue<int> q;
        par[x] = 0;
        q.push(x);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == y) break;
            for (int v : adj[u]) {
                if (par[v] == -1) {
                    par[v] = u;
                    q.push(v);
                }
            }
        }
        // Reconstruct path
        vector<int> path;
        int cur = y;
        while (cur != 0) {
            path.push_back(cur);
            cur = par[cur];
        }
        int pathLen = path.size();
        int k = rnd.next(1, pathLen);
        qs.emplace_back(x, y, k);
    }

    // Output
    println(N, M);
    println(w);
    for (auto &e : edges) println(e.first, e.second);
    for (auto &q : qs) {
        int x, y, k;
        tie(x, y, k) = q;
        println(x, y, k);
    }

    return 0;
}
