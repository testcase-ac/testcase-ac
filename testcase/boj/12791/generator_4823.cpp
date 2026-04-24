#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of queries
    int Q = rnd.next(1, 10);
    println(Q);

    for (int i = 0; i < Q; i++) {
        // Choose a mode for diversity
        int mode = rnd.next(0, 4);
        int S, E;
        if (mode == 0) {
            // Full range
            S = 1;
            E = 2016;
        } else if (mode == 1) {
            // Same year query
            S = rnd.next(1, 2016);
            E = S;
        } else if (mode == 2) {
            // Small interval of length up to 5
            S = rnd.next(1, 2016 - 5);
            E = S + rnd.next(0, 5);
        } else if (mode == 3) {
            // Medium interval of length up to 100
            S = rnd.next(1, 2016 - 100);
            E = S + rnd.next(0, 100);
        } else {
            // Fully random interval
            S = rnd.next(1, 2016);
            E = rnd.next(S, 2016);
        }
        println(S, E);
    }

    return 0;
}
