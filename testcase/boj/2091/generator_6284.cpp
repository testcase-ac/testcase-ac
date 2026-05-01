#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int X, A, B, C, D;
    int scenario = rnd.next(0, 3);

    if (scenario == 0) {
        // Plenty of pennies case
        X = rnd.next(1, 50);
        A = rnd.next(X, X + rnd.next(0, 20));
        B = rnd.next(0, 5);
        C = rnd.next(0, 3);
        D = rnd.next(0, 2);
    }
    else if (scenario == 1) {
        // No pennies: sometimes possible (if X%5==0 and enough nickels), sometimes impossible
        X = rnd.next(1, 100);
        A = 0;
        int need = (X + 4) / 5;  // minimum nickels needed if only nickels
        bool possible = rnd.next(0, 1) == 1 && X % 5 == 0;
        if (possible) {
            B = rnd.next(need, need + 3);
            C = rnd.next(0, 2);
            D = rnd.next(0, 1);
        } else {
            // force impossibility by insufficient nickels or wrong mod
            B = rnd.next(0, max(0, need - 1));
            C = rnd.next(0, 2);
            D = rnd.next(0, 1);
        }
    }
    else if (scenario == 2) {
        // Balanced random limited coins
        X = rnd.next(1, 200);
        A = rnd.next(0, X);
        B = rnd.next(0, X / 5);
        C = rnd.next(0, X / 10);
        D = rnd.next(0, X / 25);
    }
    else {
        // Large bounds test
        X = rnd.wnext(10000, 3) + 1;
        A = rnd.next(0, 10000);
        B = rnd.next(0, 10000);
        C = rnd.next(0, 10000);
        D = rnd.next(0, 10000);
    }

    println(X, A, B, C, D);
    return 0;
}
