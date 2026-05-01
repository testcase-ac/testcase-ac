#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 8);
    for (int i = 0; i < T; i++) {
        // Choose L,P with 1 < L < P
        int L = rnd.next(2, 20);
        int delta = rnd.next(1, 20);
        int P = L + delta;
        // Choose number of full cycles: sometimes small, sometimes larger
        int cycles;
        if (rnd.next(0, 1) == 0) cycles = rnd.next(1, 2);
        else cycles = rnd.next(3, 10);
        // Remainder part, ensure V > P
        int r;
        if (cycles == 1) r = rnd.next(1, P - 1);
        else r = rnd.next(0, P - 1);
        int V = P * cycles + r;
        println(L, P, V);
    }
    // Termination line
    println(0, 0, 0);
    return 0;
}
