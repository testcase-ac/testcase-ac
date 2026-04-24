#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, N);

    // Scenario types for diversity
    int scenario = rnd.next(0, 2);

    int c_lo, c_hi, w_lo, w_hi;
    if (scenario == 0) {
        // Likely fail: low capacities, high demands
        c_lo = rnd.next(1, 3);
        c_hi = rnd.next(c_lo, 5);
        w_lo = rnd.next(5, 10);
        w_hi = rnd.next(w_lo, 15);
    } else if (scenario == 1) {
        // Likely succeed: high capacities, low demands
        c_lo = rnd.next(10, 15);
        c_hi = rnd.next(c_lo, 20);
        w_lo = rnd.next(1, 3);
        w_hi = rnd.next(w_lo, 5);
    } else {
        // Mixed random
        c_lo = rnd.next(1, 10);
        c_hi = rnd.next(c_lo, 20);
        w_lo = rnd.next(1, 10);
        w_hi = rnd.next(w_lo, 20);
    }

    // Generate capacities
    vector<int> c(N);
    for (int i = 0; i < N; i++) {
        c[i] = rnd.next(c_lo, c_hi);
    }

    // Generate demands
    vector<int> w(M);
    for (int i = 0; i < M; i++) {
        w[i] = rnd.next(w_lo, w_hi);
    }

    // Generate b_i with some bias
    vector<int> b(M);
    for (int i = 0; i < M; i++) {
        int t = rnd.next(-1, 1); // bias: -1 favors small, +1 favors large
        b[i] = rnd.wnext(N, t) + 1; // 1..N
        // with small chance enforce extreme picks
        if (rnd.next(0, 9) == 0) b[i] = 1;
        if (rnd.next(0, 9) == 0) b[i] = N;
    }

    // Ensure at least one picks the smallest and one picks the largest if possible
    if (M >= 2) {
        b[0] = 1;
        b[1] = N;
    }

    // Output
    println(N, M);
    println(c);
    println(w);
    println(b);

    return 0;
}
