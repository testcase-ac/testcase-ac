/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices: between 2 and 10
    int V = rnd.next(2, 10);
    // All possible edges (undirected, i<j)
    vector<pair<int,int>> all_edges;
    for (int i = 1; i <= V; i++) {
        for (int j = i+1; j <= V; j++) {
            all_edges.emplace_back(i, j);
        }
    }
    // Determine total edges M: at least V-1 for connectivity, up to complete graph
    int minE = V - 1;
    int maxE = (int)all_edges.size();
    int M = rnd.next(minE, maxE);

    // Make a random spanning tree first to ensure connectivity
    vector<int> perm(V);
    for (int i = 0; i < V; i++) perm[i] = i+1;
    shuffle(perm.begin(), perm.end());
    // Mark tree edges
    vector<pair<int,int>> tree_edges;
    for (int i = 0; i+1 < V; i++) {
        int u = perm[i], v = perm[i+1];
        if (u > v) swap(u, v);
        tree_edges.emplace_back(u, v);
    }
    // Remove tree edges from all_edges
    vector<pair<int,int>> rest;
    for (auto &e : all_edges) {
        bool is_tree = false;
        for (auto &t : tree_edges) {
            if (e.first == t.first && e.second == t.second) {
                is_tree = true;
                break;
            }
        }
        if (!is_tree) rest.push_back(e);
    }

    // Shuffle the remaining edges
    shuffle(rest.begin(), rest.end());
    int need_extra = M - (V-1);
    rest.resize(need_extra);

    // Combine tree edges and extra edges
    vector<pair<int,int>> edges = tree_edges;
    edges.insert(edges.end(), rest.begin(), rest.end());
    // Final shuffle to mix tree and extra edges
    shuffle(edges.begin(), edges.end());

    // Choose a max absolute weight (small for hand-checkable)
    int maxW = rnd.next(1, 100);
    // Output
    println(V, M);
    for (auto &e : edges) {
        int w = rnd.next(-maxW, maxW);
        println(e.first, e.second, w);
    }

    return 0;
}
