#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for skewed N, M
    int t = rnd.next(-3, 3);
    int N = rnd.wnext(9999, t) + 2;  // [2..10000]
    int M = rnd.wnext(9999, t) + 2;

    // Select case type: 0=trivial, 1=one-op, 2=impossible, 3=random
    int caseType = rnd.next(0, 3);
    int d, e, x, y;

    if (caseType == 0) {
        // Trivial: no moves needed
        d = rnd.next(1, 10000);
        e = d;
        x = 0; y = 0;
    }
    else if (caseType == 1) {
        // One-command reachable: x = (i-1)*(d-e), y likewise
        d = rnd.next(1, 10000);
        int diff;
        do {
            diff = rnd.next(-10, 10);
        } while (diff == 0);
        e = d - diff;
        while (e < 1 || e > 10000) {
            do { diff = rnd.next(-10, 10); } while (diff == 0);
            e = d - diff;
        }
        int imax = min(N, 10);
        int jmax = min(M, 10);
        int i = rnd.next(1, imax);
        int j = rnd.next(1, jmax);
        x = (i - 1) * (d - e);
        y = (j - 1) * (d - e);
    }
    else if (caseType == 2) {
        // Impossible: spacing unchanged but non-zero target
        d = rnd.next(1, 10000);
        e = d;
        do {
            x = rnd.next(-10000, 10000);
            y = rnd.next(-10000, 10000);
        } while (x == 0 && y == 0);
    }
    else {
        // Fully random
        d = rnd.next(1, 10000);
        e = rnd.next(1, 10000);
        x = rnd.next(-10000, 10000);
        y = rnd.next(-10000, 10000);
    }

    println(N, M, d, e, x, y);
    return 0;
}
