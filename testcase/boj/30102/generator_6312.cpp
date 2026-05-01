#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of nodes small enough for manual check
    int N = rnd.next(2, 12);
    int maxEdges = N * (N - 1) / 2;
    // Ensure some variety in connectivity: sometimes enforce connected
    bool ensureConnected = rnd.next(0.0, 1.0) < 0.7;
    int M = rnd.next(N - 1, maxEdges);

    // Hyper-parameters for K and T, skewed toward smaller values but up to 6
    int cap = min(N, 6);
    int K = rnd.wnext(cap, -1) + 1;
    int T = rnd.wnext(cap, -1) + 1;

    // Pick K distinct chain store nodes, sorted
    vector<int> nodes(N);
    for (int i = 0; i < N; ++i) nodes[i] = i + 1;
    shuffle(nodes.begin(), nodes.end());
    vector<int> a(nodes.begin(), nodes.begin() + K);
    sort(a.begin(), a.end());

    // Pick T distinct farm nodes, sorted (can overlap with stores)
    shuffle(nodes.begin(), nodes.end());
    vector<int> b(nodes.begin(), nodes.begin() + T);
    sort(b.begin(), b.end());
    // Assign prices with some small and some large values
    vector<int> c(T);
    for (int i = 0; i < T; ++i) {
        if (rnd.next(0, 4) == 0) {
            c[i] = rnd.next(100000, 1000000000);
        } else {
            c[i] = rnd.next(1, 20);
        }
    }

    // Prepare edges
    vector<pair<int,int>> edges;
    if (ensureConnected) {
        // Build a random spanning tree
        vector<int> order = nodes;
        shuffle(order.begin(), order.end());
        vector<pair<int,int>> tree;
        for (int i = 1; i < N; ++i) {
            int u = order[i];
            int v = order[rnd.next(0, i - 1)];
            if (u > v) swap(u, v);
            tree.emplace_back(u, v);
        }
        edges = tree;
        // Build all remaining possible edges
        vector<pair<int,int>> cand;
        for (int u = 1; u <= N; ++u)
            for (int v = u + 1; v <= N; ++v) {
                if (!binary_search(tree.begin(), tree.end(), make_pair(u, v)))
                    cand.emplace_back(u, v);
            }
        shuffle(cand.begin(), cand.end());
        int need = M - (int)tree.size();
        for (int i = 0; i < need && i < (int)cand.size(); ++i)
            edges.push_back(cand[i]);
    } else {
        // Pure random edges (could be disconnected)
        vector<pair<int,int>> all;
        for (int u = 1; u <= N; ++u)
            for (int v = u + 1; v <= N; ++v)
                all.emplace_back(u, v);
        shuffle(all.begin(), all.end());
        edges.assign(all.begin(), all.begin() + M);
    }
    // Assign weights
    vector<tuple<int,int,int>> outE;
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        int w;
        if (rnd.next(0, 9) == 0) w = rnd.next(1, 1000);
        else w = rnd.next(1, 20);
        outE.emplace_back(u, v, w);
    }
    // Output
    println(N, M, K, T);
    println(a);
    for (int i = 0; i < T; ++i) {
        println(b[i], c[i]);
    }
    for (auto &t : outE) {
        int u, v, w;
        tie(u, v, w) = t;
        println(u, v, w);
    }
    return 0;
}
