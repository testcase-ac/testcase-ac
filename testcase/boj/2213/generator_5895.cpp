#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes, allow trivial case n=1
    int n = rnd.next(1, 15);

    // Hyper-parameter for tree shape: 0=chain, 1=star, 2=random tree
    int shape = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (shape == 0) {
        // Chain: 1-2-3-...-n
        for (int i = 1; i < n; i++)
            edges.emplace_back(i, i+1);
    } else if (shape == 1) {
        // Star: 1 is center
        for (int i = 2; i <= n; i++)
            edges.emplace_back(1, i);
    } else {
        // Random tree by parent pointer
        for (int i = 2; i <= n; i++) {
            int p = rnd.next(1, i-1);
            edges.emplace_back(p, i);
        }
    }
    // Shuffle edges to remove any order bias
    shuffle(edges.begin(), edges.end());

    // Hyper-parameter for weight cap
    vector<int> caps = {10, 100, 1000};
    int cap = rnd.any(caps);

    // Random choice: skew weights high sometimes
    bool skewHigh = rnd.next(0, 1);
    vector<int> w(n+1);
    for (int i = 1; i <= n; i++) {
        if (skewHigh) {
            // Bias towards larger weights
            w[i] = rnd.wnext(cap, 1) + 1;
        } else {
            // Uniform weights
            w[i] = rnd.next(1, cap);
        }
    }

    // Output
    println(n);
    // Print weights w[1..n]
    vector<int> wts(n);
    for (int i = 0; i < n; i++) wts[i] = w[i+1];
    println(wts);
    // Print edges
    for (auto &e : edges) {
        println(e.first, e.second);
    }
    return 0;
}
