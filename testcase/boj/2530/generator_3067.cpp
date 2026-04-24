#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: sometimes choose boundary times
    bool nearBoundary = rnd.next(0, 1);
    int A = nearBoundary ? (rnd.next(0, 1) ? 0 : 23) : rnd.next(0, 23);
    int B = nearBoundary ? (rnd.next(0, 1) ? 0 : 59) : rnd.next(0, 59);
    int C = nearBoundary ? (rnd.next(0, 1) ? 0 : 59) : rnd.next(0, 59);

    // Hyper-parameter: choose D bucket for diversity
    int bucket = rnd.next(0, 3);
    int D;
    if (bucket == 0) {
        // exact zero
        D = 0;
    } else if (bucket == 1) {
        // small seconds (<1 minute)
        D = rnd.next(1, 59);
    } else if (bucket == 2) {
        // cross one or more minutes but <1 hour
        D = rnd.next(60, 3599);
    } else {
        // large durations, possibly over a day
        if (rnd.next(0, 1)) {
            D = rnd.next(3600, 86399);
        } else {
            D = rnd.next(86400, 500000);
        }
    }

    // Output one test case
    println(A, B, C);
    println(D);

    return 0;
}
