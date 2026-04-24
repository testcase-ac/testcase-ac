#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices
    int N = rnd.next(2, 10);

    // Decide whether to force connectivity
    bool isConnected = rnd.next() < 0.5;
    vector<pair<int,int>> edges;

    if (isConnected) {
        // Build a random spanning tree first
        vector<int> nodes(N);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        set<pair<int,int>> tree_edges;
        for (int i = 1; i < N; ++i) {
            int u = nodes[i-1], v = nodes[i];
            if (u > v) swap(u, v);
            edges.emplace_back(u, v);
            tree_edges.emplace(u, v);
        }
        // Hyper-parameter: extra edge density
        double density = rnd.next(0.0, 1.0);
        // List all possible edges not in the tree
        vector<pair<int,int>> cand;
        for (int i = 1; i <= N; ++i)
            for (int j = i+1; j <= N; ++j)
                if (!tree_edges.count({i, j}))
                    cand.emplace_back(i, j);
        shuffle(cand.begin(), cand.end());
        // Add each candidate with probability = density
        for (auto &e : cand) {
            if (rnd.next() < density)
                edges.push_back(e);
        }
    } else {
        // Pure random graph by density
        double density = rnd.next(0.0, 1.0);
        for (int i = 1; i <= N; ++i) {
            for (int j = i+1; j <= N; ++j) {
                if (rnd.next() < density)
                    edges.emplace_back(i, j);
            }
        }
        // Ensure at least one edge
        if (edges.empty()) {
            int u = rnd.next(1, N), v = rnd.next(1, N);
            while (v == u) v = rnd.next(1, N);
            if (u > v) swap(u, v);
            edges.emplace_back(u, v);
        }
    }

    // Final shuffle of edges
    shuffle(edges.begin(), edges.end());
    int M = edges.size();

    // Output
    println(N, M);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
