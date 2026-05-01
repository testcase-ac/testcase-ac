#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of vertices
    int V = rnd.next(2, 10);
    int maxEdges = V * (V - 1) / 2;
    int treeEdges = V - 1;
    int poolSize = maxEdges - treeEdges;
    // Skew extra edges count
    int t_skew = rnd.next(-2, 2);
    int extra = poolSize > 0 ? rnd.wnext(poolSize + 1, t_skew) : 0;
    int M = treeEdges + extra;

    // Build a random spanning tree
    vector<int> perm(V);
    for (int i = 0; i < V; i++) perm[i] = i + 1;
    shuffle(perm.begin(), perm.end());
    vector<vector<bool>> adj(V + 1, vector<bool>(V + 1, false));
    vector<pair<int,int>> edges;
    for (int i = 1; i < V; i++) {
        int u = perm[i - 1], v = perm[i];
        adj[u][v] = adj[v][u] = true;
        edges.emplace_back(u, v);
    }

    // Collect all other potential edges
    vector<pair<int,int>> pool;
    for (int i = 1; i <= V; i++) {
        for (int j = i + 1; j <= V; j++) {
            if (!adj[i][j]) pool.emplace_back(i, j);
        }
    }
    shuffle(pool.begin(), pool.end());
    for (int i = 0; i < extra && i < (int)pool.size(); i++) {
        edges.push_back(pool[i]);
    }

    // Weight distribution mode
    int wmode = rnd.next(0, 2);
    // Random distinct start positions
    int J = rnd.next(1, V), S = rnd.next(1, V);
    while (S == J) S = rnd.next(1, V);

    // Shuffle edges before printing
    shuffle(edges.begin(), edges.end());

    // Output
    println(V, M);
    for (auto &e : edges) {
        int w;
        if (wmode == 0) w = rnd.next(1, 10);
        else if (wmode == 1) w = rnd.next(1, 100);
        else w = rnd.next(1, 10000);
        println(e.first, e.second, w);
    }
    println(J, S);
    return 0;
}
