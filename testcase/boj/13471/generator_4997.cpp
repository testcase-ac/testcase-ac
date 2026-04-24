#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for track length L
    double mode = rnd.next();
    int L;
    if (mode < 0.1) {
        L = 1;                  // minimal case
    } else if (mode < 0.3) {
        L = rnd.next(2, 5);     // small
    } else if (mode < 0.6) {
        L = rnd.next(6, 10);    // medium
    } else if (mode < 0.9) {
        L = rnd.next(11, 20);   // larger but hand-checkable
    } else {
        L = rnd.next(1, 20);    // uniform fallback
    }

    // Hyper-parameter for maximal distance S
    double smode = rnd.next();
    int S;
    if (smode < 0.1) {
        S = 1;                  // extreme small
    } else if (smode < 0.2) {
        S = L;                  // extreme large
    } else {
        S = rnd.next(1, L);     // general
    }

    // Output a single test case: L and S
    println(L, S);
    return 0;
}
