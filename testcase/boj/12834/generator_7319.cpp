#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of places
    int V = rnd.next(2, 12);
    int maxE = V * (V - 1) / 2;
    // Edge count hyper-parameter: sparse, medium, dense
    int t = rnd.next(-1, 1);
    int M;
    if (t == -1) {
        M = rnd.next(0, maxE / 3);
    } else if (t == 0) {
        int lo = maxE / 4;
        int hi = maxE / 2;
        if (lo > hi) lo = hi;
        M = rnd.next(lo, hi);
    } else {
        M = rnd.next(maxE / 2, maxE);
    }

    // Choose special nodes A (KIST) and B (Food)
    int A = rnd.next(1, V);
    int B;
    if (rnd.next(0, 3) == 0) {
        B = A;
    } else {
        B = rnd.next(1, V);
        if (B == A) B = B % V + 1;
    }

    // Number of team members
    int N = rnd.next(1, min(V, 10));
    vector<int> H(N);
    for (int i = 0; i < N; i++) {
        int r = rnd.next(0, 9);
        if (r == 0) H[i] = A;
        else if (r == 1) H[i] = B;
        else H[i] = rnd.next(1, V);
    }

    // Build all possible undirected edges
    vector<pair<int,int>> edges;
    for (int i = 1; i <= V; i++) {
        for (int j = i + 1; j <= V; j++) {
            edges.emplace_back(i, j);
        }
    }
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // Assign random weights
    vector<tuple<int,int,int>> elist;
    for (auto &e : edges) {
        int w = rnd.next(1, 100);
        elist.emplace_back(e.first, e.second, w);
    }

    // Output
    println(N, V, M);
    println(A, B);
    println(H);
    for (auto &tup : elist) {
        int u, v, w;
        tie(u, v, w) = tup;
        println(u, v, w);
    }

    return 0;
}
