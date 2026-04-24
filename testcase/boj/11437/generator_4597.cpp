#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size
    int N = rnd.next(2, 10);
    // Hyper-parameter: tree shape type
    int treeType = rnd.next(0, 2);

    vector<int> parent(N + 1);
    vector<pair<int,int>> edges;
    parent[1] = 0;
    if (treeType == 0) {
        // Chain
        for (int i = 2; i <= N; ++i) {
            parent[i] = i - 1;
            edges.emplace_back(i - 1, i);
        }
    } else if (treeType == 1) {
        // Star
        for (int i = 2; i <= N; ++i) {
            parent[i] = 1;
            edges.emplace_back(1, i);
        }
    } else {
        // Random tree
        for (int i = 2; i <= N; ++i) {
            int p = rnd.next(1, i - 1);
            parent[i] = p;
            edges.emplace_back(p, i);
        }
    }
    shuffle(edges.begin(), edges.end());

    // Output the tree
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);

    // Precompute ancestor lists
    vector<vector<int>> anc(N + 1);
    for (int i = 1; i <= N; ++i) {
        int x = i;
        while (x != 0) {
            anc[i].push_back(x);
            x = parent[x];
        }
    }

    // Number of queries
    int maxPairs = N * (N - 1) / 2;
    int M = rnd.next(1, min(maxPairs, 20));
    // Hyper-parameter: probability of ancestor-ancestor queries
    double ancProb = rnd.next(0.0, 1.0);

    auto isAncestor = [&](int a, int b) {
        for (int x : anc[b]) if (x == a) return true;
        return false;
    };

    vector<pair<int,int>> qs;
    while ((int)qs.size() < M) {
        if (rnd.next() < ancProb) {
            // Ensure one is ancestor of the other
            int u = rnd.next(1, N);
            if ((int)anc[u].size() > 1) {
                int idx = rnd.next(1, (int)anc[u].size() - 1);
                int v = anc[u][idx];
                qs.emplace_back(u, v);
            } else {
                // Fallback to random distinct
                int u1 = rnd.next(1, N), v1 = rnd.next(1, N);
                while (v1 == u1) v1 = rnd.next(1, N);
                qs.emplace_back(u1, v1);
            }
        } else {
            // Ensure neither is ancestor of the other
            int u = rnd.next(1, N), v = rnd.next(1, N);
            int tries = 0;
            while ((u == v || isAncestor(u, v) || isAncestor(v, u)) && tries < 10) {
                u = rnd.next(1, N);
                v = rnd.next(1, N);
                ++tries;
            }
            if (u == v || isAncestor(u, v) || isAncestor(v, u)) {
                // Fallback
                u = rnd.next(1, N);
                v = rnd.next(1, N);
                while (v == u) v = rnd.next(1, N);
            }
            qs.emplace_back(u, v);
        }
    }

    // Output queries
    println(M);
    for (auto &p : qs)
        println(p.first, p.second);

    return 0;
}
