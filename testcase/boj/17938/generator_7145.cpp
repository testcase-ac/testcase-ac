#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sample N in small, medium, or large range
    int grp = rnd.next(1, 3);
    int N;
    if (grp == 1) {
        N = rnd.next(2, 10);
    } else if (grp == 2) {
        N = rnd.next(11, 100);
    } else {
        N = rnd.next(101, 1000);
    }

    // Compute one full up-and-down cycle length
    int period = 4 * N - 2;

    // Sample T with different patterns
    int tcase = rnd.next(1, 4);
    int T;
    if (tcase == 1) {
        // small T near start
        T = rnd.next(1, 2 * N);
    } else if (tcase == 2) {
        // around one period boundary
        int lo = max(1, period - 5);
        int hi = period + 5;
        T = rnd.next(lo, hi);
    } else if (tcase == 3) {
        // arbitrary within full constraint
        T = rnd.next(1, 10000000);
    } else {
        // exactly maximum T
        T = 10000000;
    }

    // Sample P as edge or random position
    int pcase = rnd.next(1, 3);
    int P;
    if (pcase == 1) {
        P = 1;
    } else if (pcase == 2) {
        P = N;
    } else {
        P = rnd.next(1, N);
    }

    // Output
    println(N);
    println(P, T);

    return 0;
}
