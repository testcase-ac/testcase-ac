#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes
    int N = rnd.next(1, 10);

    // Generate a random tree by linking each node 2..N to a random previous node
    vector<pair<int,int>> edges;
    for (int i = 2; i <= N; ++i) {
        int p = rnd.next(1, i - 1);
        edges.emplace_back(p, i);
    }

    // Hyper-parameter for edge-direction swaps to add diversity
    double swapProb = rnd.next(0.0, 1.0);
    shuffle(edges.begin(), edges.end());
    for (auto &e : edges) {
        if (rnd.next() < swapProb)
            swap(e.first, e.second);
    }

    // Number of queries
    int M = rnd.next(1, min(20, N * 2));

    // Output the tree
    println(N);
    for (auto &e : edges)
        println(e.first, e.second);

    // Output queries with diverse patterns
    println(M);
    for (int i = 0; i < M; ++i) {
        int t = rnd.next(0, 3);
        int r, u, v;
        switch (t) {
            case 0:
                // All random
                r = rnd.next(1, N);
                u = rnd.next(1, N);
                v = rnd.next(1, N);
                break;
            case 1:
                // u == v
                r = rnd.next(1, N);
                u = rnd.next(1, N);
                v = u;
                break;
            case 2:
                // r == u
                r = rnd.next(1, N);
                u = r;
                v = rnd.next(1, N);
                break;
            default:
                // r == v
                r = rnd.next(1, N);
                v = r;
                u = rnd.next(1, N);
                break;
        }
        println(r, u, v);
    }

    return 0;
}
