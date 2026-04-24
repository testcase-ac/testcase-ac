#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for randomness
    int n = rnd.next(1, 10);               // number of nodes
    double chain_prob = rnd.next(0.0, 1.0); // probability to attach in a chain
    int maxW = rnd.next(1, 100);           // maximum edge weight

    // Generate a random rooted tree with root = 1
    // and weights in [1, maxW]
    vector<tuple<int,int,int>> edges;
    for (int i = 2; i <= n; i++) {
        int parent;
        if (rnd.next() < chain_prob) {
            // make a chain edge
            parent = i - 1;
        } else {
            // attach to any earlier node
            parent = rnd.next(1, i - 1);
        }
        int w = rnd.next(1, maxW);
        edges.emplace_back(parent, i, w);
    }

    // Sort edges by parent then child, to match input guarantee
    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b) {
             if (get<0>(a) != get<0>(b))
                 return get<0>(a) < get<0>(b);
             return get<1>(a) < get<1>(b);
         });

    // Output
    println(n);
    for (auto &e : edges) {
        int p, c, w;
        tie(p, c, w) = e;
        println(p, c, w);
    }
    return 0;
}
