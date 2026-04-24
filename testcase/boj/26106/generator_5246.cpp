#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of vertices
    int n = rnd.next(2, 10);
    // Maximum possible directed edges without self-loops
    int maxPossible = n * (n - 1);
    // Bound by problem constraint m <= 10n
    int maxEdges = min(maxPossible, 10 * n);
    // Choose number of edges
    int m = rnd.next(1, maxEdges);

    // Build all possible directed edges (no self-loops)
    vector<pair<int,int>> cand;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u != v) cand.emplace_back(u, v);
        }
    }
    shuffle(cand.begin(), cand.end());

    // Select m edges while enforcing out-degree <= 10
    vector<pair<int,int>> edges;
    vector<int> outdeg(n, 0);
    for (auto &e : cand) {
        if ((int)edges.size() >= m) break;
        int u = e.first;
        if (outdeg[u] < 10) {
            edges.push_back(e);
            outdeg[u]++;
        }
    }

    // Source and target
    int src = rnd.next(0, n-1);
    int dst = rnd.next(0, n-1);

    // Build adjacency lists for forbidden-turn candidates
    vector<vector<int>> from(n), to(n);
    for (auto &e : edges) {
        int x = e.first, y = e.second;
        from[y].push_back(x);
        to[x].push_back(y);
    }
    // Collect all possible (x,y,z) with edges x->y and y->z
    vector<array<int,3>> candTurns;
    for (int y = 0; y < n; y++) {
        for (int x : from[y]) {
            for (int z : to[y]) {
                candTurns.push_back({x, y, z});
            }
        }
    }
    shuffle(candTurns.begin(), candTurns.end());

    // Choose number of forbidden turns k with some diversity
    int T = candTurns.size();
    int k = 0;
    if (T > 0) {
        double p = rnd.next();
        if (p < 0.3) {
            k = 0;
        } else if (p < 0.6) {
            k = rnd.next(1, min(T, 3));
        } else {
            k = rnd.next(min(T, 3), T);
        }
    }

    // Output
    println(m, n, k);
    println(src, dst);
    // Edge costs small
    for (auto &e : edges) {
        int c = rnd.next(0, 20);
        println(e.first, e.second, c);
    }
    // Forbidden turns
    for (int i = 0; i < k; i++) {
        auto t = candTurns[i];
        println(t[0], t[1], t[2]);
    }
    return 0;
}
