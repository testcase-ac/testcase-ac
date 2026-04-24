#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);      // number of countries
    int M = rnd.next(1, 10);      // number of zones
    int Q = rnd.next(1, 10);      // number of forecasts

    // Zone ownership: o_i in [1..N]
    vector<int> zones(M);
    for (int i = 0; i < M; i++) {
        zones[i] = rnd.next(1, N);
    }

    // Thresholds p_j, up to 200 to allow some NIE cases
    vector<int> p(N);
    for (int j = 0; j < N; j++) {
        p[j] = rnd.next(1, 200);
    }

    // Forecasts
    vector<int> L(Q), R(Q), A(Q);
    for (int u = 0; u < Q; u++) {
        // decide segment type
        if (M >= 2 && rnd.next(0, 1) == 1) {
            // wrap-around: l > r
            R[u] = rnd.next(1, M - 1);
            L[u] = rnd.next(R[u] + 1, M);
        } else {
            // normal: l <= r
            L[u] = rnd.next(1, M);
            R[u] = rnd.next(L[u], M);
        }
        A[u] = rnd.next(1, 20);  // meteors per zone
    }

    // Output
    println(N, M);
    println(zones);
    println(p);
    println(Q);
    for (int u = 0; u < Q; u++) {
        println(L[u], R[u], A[u]);
    }

    return 0;
}
