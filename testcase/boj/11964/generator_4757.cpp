#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Maximum fullness T
    int T = rnd.next(1, 50);

    int A, B;
    // With some probability make A == B
    if (rnd.next(1, 5) == 1) {
        int v = rnd.next(1, T);
        A = B = v;
    } else {
        // Define size categories for diversity
        int hi_small = max(1, T / 10);
        int lo_med = max(1, T / 3);
        int hi_med = max(lo_med, (2 * T) / 3);
        int lo_large = max(1, T / 2);

        // Pick A
        int cat = rnd.next(0, 2);
        if (cat == 0) {
            A = rnd.next(1, hi_small);
        } else if (cat == 1) {
            A = rnd.next(lo_med, hi_med);
        } else {
            A = rnd.next(lo_large, T);
        }

        // Pick B
        cat = rnd.next(0, 2);
        if (cat == 0) {
            B = rnd.next(1, hi_small);
        } else if (cat == 1) {
            B = rnd.next(lo_med, hi_med);
        } else {
            B = rnd.next(lo_large, T);
        }
    }

    // Output the single test case
    println(T, A, B);
    return 0;
}
