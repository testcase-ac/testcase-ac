#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int MAX = 20;
    const int HALF = MAX / 2;
    const int QUART = MAX / 4;

    int atkA, hpA, atkB, hpB;
    int htype = rnd.next(0, 2);

    if (htype == 0) {
        // Pure random
        atkA = rnd.next(1, MAX);
        hpA  = rnd.next(1, MAX);
        atkB = rnd.next(1, MAX);
        hpB  = rnd.next(1, MAX);
    }
    else if (htype == 1) {
        // Force a DRAW: same number of rounds
        while (true) {
            atkA = rnd.next(1, MAX);
            atkB = rnd.next(1, MAX);
            int maxrA = MAX / atkB;
            int maxrB = MAX / atkA;
            int maxr = min(maxrA, maxrB);
            if (maxr >= 1) {
                int r = rnd.next(1, maxr);
                hpA = r * atkB;
                hpB = r * atkA;
                break;
            }
        }
    }
    else {
        // Extreme who-wins case
        int who = rnd.next(0, 1);
        if (who == 0) {
            // Ensure A wins decisively
            atkA = rnd.next(HALF + 1, MAX);
            hpA  = rnd.next(1, max(1, QUART));
            atkB = rnd.next(1, HALF);
            hpB  = rnd.next(HALF + 1, MAX);
        } else {
            // Ensure B wins decisively
            atkB = rnd.next(HALF + 1, MAX);
            hpB  = rnd.next(1, max(1, QUART));
            atkA = rnd.next(1, HALF);
            hpA  = rnd.next(HALF + 1, MAX);
        }
    }

    // Output the two cards
    println(atkA, hpA);
    println(atkB, hpB);
    return 0;
}
