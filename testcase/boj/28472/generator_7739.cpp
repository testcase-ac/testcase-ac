#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int N = rnd.next(2, 12);
    // Root node
    int R = rnd.next(1, N);

    // Decide tree shape: 0 = chain, 1 = star, 2 = random
    int shape = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    vector<int> nodes(N);
    for (int i = 0; i < N; i++) nodes[i] = i+1;

    if (shape == 0) {
        // Chain
        shuffle(nodes.begin(), nodes.end());
        for (int i = 0; i+1 < N; i++) {
            edges.emplace_back(nodes[i], nodes[i+1]);
        }
    } else if (shape == 1) {
        // Star centered at root
        for (int v = 1; v <= N; v++) if (v != R) {
            edges.emplace_back(R, v);
        }
    } else {
        // Random tree
        vector<int> inserted;
        inserted.push_back(R);
        vector<int> others;
        for (int v = 1; v <= N; v++) if (v != R) others.push_back(v);
        shuffle(others.begin(), others.end());
        for (int v : others) {
            int p = rnd.any(inserted);
            edges.emplace_back(p, v);
            inserted.push_back(v);
        }
    }

    // Build directed tree to find leaves
    vector<vector<int>> adj(N+1);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    vector<vector<int>> children(N+1);
    vector<int> stk;
    vector<int> parent(N+1, 0);
    stk.push_back(R);
    parent[R] = -1;
    while (!stk.empty()) {
        int u = stk.back(); stk.pop_back();
        for (int v : adj[u]) {
            if (parent[v] == 0) {
                parent[v] = u;
                children[u].push_back(v);
                stk.push_back(v);
            }
        }
    }
    // Collect leaves
    vector<int> leaves;
    for (int u = 1; u <= N; u++) {
        if (children[u].empty()) leaves.push_back(u);
    }
    int L = leaves.size();

    // Assign leaf values with some extremes
    vector<int> leaf_vals(L);
    for (int i = 0; i < L; i++) {
        if (rnd.next(0,4) == 0) {
            leaf_vals[i] = rnd.next(1000000000-10, 1000000000);
        } else {
            leaf_vals[i] = rnd.next(0, 20);
        }
    }

    // Queries
    int Q = rnd.next(1, min(N, 10));
    vector<int> queries(Q);
    for (int i = 0; i < Q; i++) {
        queries[i] = rnd.next(1, N);
    }

    // Output
    println(N, R);
    for (auto &e : edges) println(e.first, e.second);
    println(L);
    for (int i = 0; i < L; i++) {
        println(leaves[i], leaf_vals[i]);
    }
    println(Q);
    for (int q : queries) println(q);

    return 0;
}
