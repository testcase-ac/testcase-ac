#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: number of rooms
    int n = rnd.next(2, 10);

    // We ensure undirected connectivity by a random tree (n-1 edges)
    // Then we can add extra directed edges up to n*(n-1)
    int maxEdges = n * (n - 1);
    int minEdges = n - 1;
    int maxExtra = maxEdges - minEdges;

    // Hyperparameter: bias for extra edges count
    vector<int> ts = {-3, -2, -1, 0, 1, 2, 3};
    int t = rnd.any(ts);
    // extra in [0..maxExtra], biased by wnext
    int extra = rnd.wnext(maxExtra + 1, t);
    int m = minEdges + extra;

    // Build a random tree to guarantee connectivity (undirected)
    vector<pair<int,int>> edges;
    edges.reserve(m);
    for (int v = 2; v <= n; v++) {
        int u = rnd.next(1, v - 1);
        // Random orientation for this tree edge
        if (rnd.next(0,1) == 0)
            edges.emplace_back(u, v);
        else
            edges.emplace_back(v, u);
    }

    // Mark existing directed edges
    vector< vector<bool> > used(n+1, vector<bool>(n+1, false));
    for (auto &e : edges) {
        used[e.first][e.second] = true;
    }

    // Build candidate extra edges (all u!=v and not used)
    vector<pair<int,int>> cand;
    cand.reserve(maxExtra);
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (u == v) continue;
            if (!used[u][v]) {
                cand.emplace_back(u, v);
            }
        }
    }

    // Shuffle and pick 'extra' edges
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < extra; i++) {
        edges.push_back(cand[i]);
    }

    // Final shuffle of all edges for randomness
    shuffle(edges.begin(), edges.end());

    // Output
    println(n, m);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
