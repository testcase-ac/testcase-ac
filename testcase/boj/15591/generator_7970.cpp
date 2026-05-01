#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: size of tree and number of queries
    int N = rnd.next(2, 10);
    int Q = rnd.next(1, 10);

    // Maximum edge weight
    int maxR = rnd.next(5, 100);

    // Decide tree shape: chain or random
    bool chain = rnd.next(0, 1) == 0;
    vector< tuple<int,int,int> > edges;
    for (int i = 2; i <= N; ++i) {
        int u = i;
        int v = chain ? i - 1 : rnd.next(1, i - 1);
        int r = rnd.next(1, maxR);
        edges.emplace_back(u, v, r);
    }
    shuffle(edges.begin(), edges.end());

    // Output N, Q
    println(N, Q);
    // Output edges
    for (auto &e : edges) {
        int u, v, r;
        tie(u, v, r) = e;
        println(u, v, r);
    }

    // Generate queries with diverse K values
    for (int i = 0; i < Q; ++i) {
        int t = rnd.next(0, 3);
        int k;
        if (t == 0) {
            // very low threshold
            k = 1;
        } else if (t == 1) {
            // exactly equal to some maximum edge weight
            k = maxR;
        } else if (t == 2) {
            // above all weights to test zero-result
            k = rnd.next(maxR + 1, maxR + 100);
        } else {
            // arbitrary mid-range
            k = rnd.next(1, maxR);
        }
        int v = rnd.next(1, N);
        println(k, v);
    }

    return 0;
}
