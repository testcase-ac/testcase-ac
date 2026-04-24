#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    for (int i = 0; i < T; i++) {
        // Which side is unknown: 0->a, 1->b, 2->c
        int u = rnd.next(0, 2);
        int a, b, c;
        // Hyper-parameter for known-side scale: small or up to 10000
        int maxKnown = rnd.next(0, 1) ? 20 : 10000;
        if (u == 2) {
            // Hypotenuse unknown: always valid
            a = rnd.next(1, maxKnown);
            b = rnd.next(1, maxKnown);
            c = -1;
        } else {
            // Decide if this case should be a valid triangle or impossible
            bool wantValid = rnd.next() >= 0.3;  // ~70% valid
            if (u == 0) {
                // a is unknown
                if (wantValid) {
                    // Ensure c > b for real positive a
                    b = rnd.next(1, maxKnown / 2);
                    int delta = rnd.next(1, maxKnown - b);
                    c = b + delta;
                } else {
                    // Make c <= b to force invalid
                    b = rnd.next(1, maxKnown);
                    c = rnd.next(1, b);
                }
                a = -1;
            } else {
                // b is unknown
                if (wantValid) {
                    a = rnd.next(1, maxKnown / 2);
                    int delta = rnd.next(1, maxKnown - a);
                    c = a + delta;
                } else {
                    a = rnd.next(1, maxKnown);
                    c = rnd.next(1, a);
                }
                b = -1;
            }
        }
        // Output one test case
        println(a, b, c);
    }
    // Termination line
    println(0, 0, 0);
    return 0;
}
