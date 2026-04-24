#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: mostly small, sometimes larger
    int N;
    if (rnd.next() < 0.7) {
        N = rnd.next(2, 15);
    } else {
        N = rnd.next(16, 90);
    }

    // Hyper-parameter for T: sometimes small, sometimes close to N
    int T;
    if (rnd.next() < 0.5) {
        int mx = max(1, N / 3);
        T = rnd.next(1, mx);
    } else {
        int lb = max(1, (2 * N) / 3);
        int ub = N - 1;
        T = rnd.next(lb, ub);
    }

    // Hyper-parameter for C: capacity, small vs large
    int C;
    if (rnd.next() < 0.6) {
        C = rnd.next(1, min(20, 300));
    } else {
        C = rnd.next(21, 300);
    }

    // Hyper-parameter for P: price per fruit, small vs large
    int P;
    if (rnd.next() < 0.6) {
        P = rnd.next(1, 100);
    } else {
        P = rnd.next(101, 1000);
    }

    // Output the single test case
    println(N, T, C, P);
    return 0;
}
