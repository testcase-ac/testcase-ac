#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of vertices
    int V = rnd.next(2, 12);
    // Tree shape: 0 = chain, 1 = star, 2 = random
    int shape = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (shape == 0) {
        // chain 1-2-3-...-V
        for (int i = 1; i < V; i++) {
            edges.emplace_back(i, i+1);
        }
    } else if (shape == 1) {
        // star around a random center
        int center = rnd.next(1, V);
        for (int i = 1; i <= V; i++) {
            if (i != center) edges.emplace_back(center, i);
        }
    } else {
        // random tree by assigning a parent for each new node
        for (int i = 2; i <= V; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    }
    // Weight bias: -1 = smaller weights, 0 = uniform, +1 = larger weights
    int bias = rnd.next(-1, 1);
    vector<vector<pair<int,int>>> adj(V+1);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        int w1 = rnd.next(1, 10000);
        int w;
        if (bias > 0) {
            w = max(w1, rnd.next(1, 10000));
        } else if (bias < 0) {
            w = min(w1, rnd.next(1, 10000));
        } else {
            w = w1;
        }
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    // Output
    println(V);
    for (int i = 1; i <= V; i++) {
        // each line: node_id (neighbor weight)* -1
        printf("%d", i);
        shuffle(adj[i].begin(), adj[i].end());
        for (auto &pr : adj[i]) {
            printf(" %d %d", pr.first, pr.second);
        }
        printf(" -1\n");
    }
    return 0;
}
