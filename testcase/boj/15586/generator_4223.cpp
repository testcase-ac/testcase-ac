#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(2, 10);
    int Q = rnd.next(1, 10);

    // Hyper-parameter for max edge weight diversity
    int tR = rnd.next(-2, 2);
    // rnd.wnext(100, tR) in [0,99], +1 -> [1,100]
    int maxR = rnd.wnext(100, tR) + 1;

    // Build a random tree without mutating the loop variable
    vector<tuple<int,int,int>> edges;
    for (int u = 2; u <= N; ++u) {
        int v = rnd.next(1, u - 1);
        int r = rnd.next(1, maxR);
        int uu = u, vv = v;
        // Flip occasionally for diversity
        if (rnd.next() < 0.5) swap(uu, vv);
        edges.emplace_back(uu, vv, r);
    }
    shuffle(edges.begin(), edges.end());

    // Generate queries with some high-K and normal-K cases
    vector<pair<int,int>> queries;
    for (int i = 0; i < Q; ++i) {
        int k;
        if (rnd.next() < 0.2) {
            // sometimes ask K above all edge weights
            k = rnd.next(maxR + 1, maxR + 20);
        } else {
            // normal range
            k = rnd.next(1, maxR);
        }
        int v = rnd.next(1, N);
        queries.emplace_back(k, v);
    }

    // Output
    println(N, Q);
    for (auto &e : edges) {
        int u, v, r;
        tie(u, v, r) = e;
        println(u, v, r);
    }
    for (auto &qr : queries) {
        println(qr.first, qr.second);
    }

    return 0;
}
