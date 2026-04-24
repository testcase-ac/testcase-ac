#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int n = rnd.next(2, 10);
    // Maximum possible edges
    int maxEdges = n * (n - 1) / 2;
    // We'll always build a spanning tree plus some extra edges
    int treeEdges = n - 1;
    int extraMax = maxEdges - treeEdges;
    int E = rnd.next(0, extraMax);
    int M = treeEdges + E;

    // Generate a random spanning tree
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());
    set<pair<int,int>> used;
    vector<pair<int,int>> edges;
    for (int i = 1; i < n; i++) {
        int parent = rnd.next(0, i - 1);
        int u = nodes[i], v = nodes[parent];
        if (u > v) swap(u, v);
        used.insert({u, v});
        edges.emplace_back(u, v);
    }
    // Generate extra edges
    vector<pair<int,int>> cand;
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            if (!used.count({u, v})) {
                cand.emplace_back(u, v);
            }
        }
    }
    shuffle(cand.begin(), cand.end());
    for (int i = 0; i < E; i++) {
        edges.push_back(cand[i]);
    }

    // Hyper-parameters for weights
    int W = rnd.any(vector<int>{5, 10, 20});
    int t = rnd.next(-2, 2);
    double dupProb = 0.3;

    // Shuffle edges so tree edges aren't always first
    shuffle(edges.begin(), edges.end());

    // Output
    println(n, M);
    for (auto &e : edges) {
        int w;
        if (rnd.next() < dupProb) {
            // force some small weights for duplicates
            w = rnd.next(1, min(5, W));
        } else {
            if (t == 0) {
                w = rnd.next(1, W);
            } else {
                // wnext gives [0, W-1], so +1
                w = rnd.wnext(W, t) + 1;
                if (w > W) w = W;
                if (w < 1) w = 1;
            }
        }
        println(e.first, e.second, w);
    }

    return 0;
}
