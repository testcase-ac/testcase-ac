#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of islands
    int n = rnd.next(1, 10);
    vector<pair<int,int>> edges;

    // Hyper-parameters
    double p_out = rnd.next();          // probability of an outgoing zip-line
    bool modeCycle = rnd.next() < 0.5;  // whether to force a large cycle

    auto pickTarget = [&](int v) {
        // pick w in [0, n-1], w != v
        int w;
        do {
            w = rnd.next(0, n-1);
        } while (w == v);
        return w;
    };

    if (modeCycle && n >= 2) {
        // Create one cycle of random size between 2 and n
        int k = rnd.next(2, n);
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        shuffle(ord.begin(), ord.end());
        vector<bool> inCycle(n, false);
        for (int i = 0; i < k; i++) {
            inCycle[ord[i]] = true;
        }
        // Build the cycle edges
        for (int i = 0; i < k; i++) {
            int u = ord[i];
            int v = ord[(i + 1) % k];
            edges.emplace_back(u, v);
        }
        // Attach the remaining vertices randomly
        for (int v = 0; v < n; v++) {
            if (inCycle[v]) continue;
            if (rnd.next() < p_out) {
                edges.emplace_back(v, pickTarget(v));
            }
        }
    } else {
        // Pure random mapping: each vertex has an outgoing with prob p_out
        for (int v = 0; v < n; v++) {
            if (n >= 2 && rnd.next() < p_out) {
                edges.emplace_back(v, pickTarget(v));
            }
        }
    }

    // Shuffle edge order for diversity
    shuffle(edges.begin(), edges.end());

    int m = edges.size();
    // Output format: m n
    println(m, n);
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
