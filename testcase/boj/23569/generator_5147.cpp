#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of vertices for hand‐checking
    int n = rnd.next(2, 10);

    // Adjacency matrix
    vector<vector<bool>> adj(n+1, vector<bool>(n+1, false));

    // Choose a mode for diversity
    // 0 = complete graph, 1 = empty graph,
    // 2 = random density, 3 = two cliques, 4 = impossible (odd cycle in complement)
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        // Complete graph
        for (int i = 1; i <= n; i++)
            for (int j = i+1; j <= n; j++)
                adj[i][j] = adj[j][i] = true;

    } else if (mode == 1) {
        // Empty graph: do nothing

    } else if (mode == 2) {
        // Random graph with random density
        double density = rnd.next(0, 100) / 100.0;
        for (int i = 1; i <= n; i++) {
            for (int j = i+1; j <= n; j++) {
                if (rnd.next() < density)
                    adj[i][j] = adj[j][i] = true;
            }
        }

    } else if (mode == 3) {
        // Exactly two cliques (complement is bipartite)
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 1);
        shuffle(ids.begin(), ids.end());
        int s = rnd.next(1, n-1);
        vector<bool> inA(n+1, false);
        for (int i = 0; i < s; i++)
            inA[ids[i]] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = i+1; j <= n; j++) {
                if (inA[i] == inA[j])
                    adj[i][j] = adj[j][i] = true;
            }
        }

    } else /* mode == 4 */ {
        // Start with complete graph
        for (int i = 1; i <= n; i++)
            for (int j = i+1; j <= n; j++)
                adj[i][j] = adj[j][i] = true;
        // Try to remove an odd cycle from the complement
        vector<int> ks;
        for (int k : {3, 5, 7})
            if (k <= n) ks.push_back(k);
        if (!ks.empty()) {
            int k = rnd.any(ks);
            vector<int> ids(n);
            iota(ids.begin(), ids.end(), 1);
            shuffle(ids.begin(), ids.end());
            vector<int> cycle(ids.begin(), ids.begin() + k);
            for (int i = 0; i < k; i++) {
                int u = cycle[i];
                int v = cycle[(i+1) % k];
                // Remove edge in complement => add edge here to break bipartiteness
                adj[u][v] = adj[v][u] = false;
            }
        }
        // If ks was empty (n<3), we leave it as a complete graph,
        // which is still bipartite-complement and trivial case.
    }

    // Collect edges
    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (adj[i][j])
                edges.emplace_back(i, j);
        }
    }
    shuffle(edges.begin(), edges.end());

    // Output
    int m = edges.size();
    println(n, m);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
