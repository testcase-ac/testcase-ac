#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence length
    int N = rnd.next(1, 10);
    // Initial value range: mostly small, sometimes large
    int initialMax = (rnd.next(0, 4) == 0 ? rnd.next(1, 1000000000) : rnd.next(1, 100));

    // Generate initial array
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(1, initialMax);
    }

    // Number of queries
    int M = rnd.next(1, 20);
    // Probability of an update-type query
    double pUpd = rnd.next(0.0, 1.0);
    // Update values up to this max (diverse)
    int updMax = rnd.next(1, 1000000000);

    // Generate operations
    struct Op { int t, a, b; };
    vector<Op> ops;
    int cntQ = 0;
    for (int k = 0; k < M; k++) {
        if (rnd.next() < pUpd) {
            // Update: 1 i v
            int idx = rnd.next(1, N);
            int v = rnd.next(1, updMax);
            ops.push_back({1, idx, v});
        } else {
            // Query: 2 i j
            int i = rnd.next(1, N);
            int j = rnd.next(i, N);
            ops.push_back({2, i, j});
            cntQ++;
        }
    }
    // Ensure at least one query
    if (cntQ == 0) {
        int k = rnd.next(0, M - 1);
        int i = rnd.next(1, N);
        int j = rnd.next(i, N);
        ops[k] = {2, i, j};
    }

    // Output
    println(N);
    println(A);
    println(M);
    for (auto &o : ops) {
        println(o.t, o.a, o.b);
    }

    return 0;
}
