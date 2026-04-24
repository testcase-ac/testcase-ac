#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with bias towards small, occasionally medium
    int N;
    if (rnd.next() < 0.7) {
        // biased to small values 1..20
        N = rnd.wnext(20, -2); // min of 3 samples
        N = max(1, N);
    } else {
        // medium values 10..20
        N = rnd.next(10, 20);
    }

    // Build a random permutation A of size N
    vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = i + 1;
    shuffle(A.begin(), A.end());

    // Choose M constraints: from 0 up to min(3*N,30)
    int M;
    if (rnd.next() < 0.5) {
        M = rnd.next(0, N);
    } else {
        M = rnd.next(N, min(3 * N, 30));
    }

    // Decide if we want a contradictory case
    bool consistent = rnd.next() < 0.8;
    if (!consistent && M == 0) M = 1;

    // Generate constraints
    struct C { int t, x, y, v; };
    vector<C> cons;
    cons.reserve(M);

    for (int i = 0; i < M; i++) {
        int x = rnd.next(1, N);
        int y = rnd.next(x, N);
        int t = rnd.next(1, 2);
        int v0;
        if (t == 1) {
            // max in [x,y]
            v0 = A[x-1];
            for (int j = x; j <= y; j++) if (A[j-1] > v0) v0 = A[j-1];
        } else {
            // min in [x,y]
            v0 = A[x-1];
            for (int j = x; j <= y; j++) if (A[j-1] < v0) v0 = A[j-1];
        }
        int v = v0;
        // if it's the last constraint and we want an inconsistency, break consistency
        if (!consistent && i == M-1) {
            // choose a wrong value in [1,N] different from v0
            if (N > 1) {
                do { v = rnd.next(1, N); } while (v == v0);
            } else {
                v = v0 == 1 ? 1 : 1;
            }
        }
        cons.push_back({t, x, y, v});
    }

    // Shuffle constraints to vary order
    shuffle(cons.begin(), cons.end());

    // Output
    println(N, M);
    for (auto &c : cons) {
        println(c.t, c.x, c.y, c.v);
    }
    return 0;
}
