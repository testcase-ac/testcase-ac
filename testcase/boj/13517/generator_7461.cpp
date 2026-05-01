#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int N = rnd.next(2, 12);

    // Generate weights with variability
    vector<int> w(N+1);
    int typeW = rnd.next(0, 2);
    if (typeW == 0) {
        // Uniform random
        for (int i = 1; i <= N; i++) {
            w[i] = rnd.next(1, 20);
        }
    } else if (typeW == 1) {
        // Increasing with noise
        for (int i = 1; i <= N; i++) {
            w[i] = i;
        }
        for (int i = 1; i <= N; i++) {
            int delta = rnd.next(-2, 2);
            w[i] = max(1, w[i] + delta);
        }
    } else {
        // Clustered around two centers
        int c1 = rnd.next(1, 20);
        int c2 = rnd.next(1, 20);
        for (int i = 1; i <= N; i++) {
            if (rnd.next() < 0.7) {
                w[i] = max(1, c1 + rnd.next(-3, 3));
            } else {
                w[i] = max(1, c2 + rnd.next(-3, 3));
            }
        }
    }

    // Generate tree shape
    vector<pair<int,int>> edges;
    int shapeType = rnd.next(0, 2);
    if (shapeType == 0) {
        // Chain
        for (int i = 1; i < N; i++) edges.emplace_back(i, i+1);
    } else if (shapeType == 1) {
        // Star
        int center = rnd.next(1, N);
        for (int i = 1; i <= N; i++) if (i != center) edges.emplace_back(center, i);
    } else {
        // Random spanning tree
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    }
    shuffle(edges.begin(), edges.end());

    // Build adjacency for path queries
    vector<vector<int>> adj(N+1);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    // Number of queries
    int M = rnd.next(1, 15);

    // Output
    println(N);
    // weights from 1 to N
    vector<int> wv(N);
    for (int i = 1; i <= N; i++) wv[i-1] = w[i];
    println(wv);
    for (auto &e : edges) println(e.first, e.second);
    println(M);

    // Generate queries
    for (int qi = 0; qi < M; qi++) {
        int u = rnd.next(1, N);
        int v = rnd.next(1, N);
        // BFS to find path from u to v
        vector<int> parent(N+1, -1);
        queue<int> q;
        parent[u] = 0;
        q.push(u);
        while (!q.empty() && parent[v] == -1) {
            int x = q.front(); q.pop();
            for (int y : adj[x]) {
                if (parent[y] == -1) {
                    parent[y] = x;
                    q.push(y);
                }
            }
        }
        vector<int> path;
        int cur = v;
        while (cur != 0) {
            path.push_back(cur);
            cur = parent[cur];
        }
        reverse(path.begin(), path.end());
        int len = path.size();
        int k = rnd.next(1, len);
        println(u, v, k);
    }

    return 0;
}
