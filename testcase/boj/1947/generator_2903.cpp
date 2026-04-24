#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: decide scale of N
    double p = rnd.next();
    int N;
    if (p < 0.8) {
        // small, hand-checkable
        N = rnd.next(1, 10);
    } else if (p < 0.95) {
        // medium
        N = rnd.next(11, 1000);
    } else {
        // large edge
        N = rnd.next(1000, 1000000);
    }

    // Output single-test input
    println(N);

    return 0;
}
