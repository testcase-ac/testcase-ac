#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to diversify N selection
    // mode 0: minimal edge case
    // mode 1: bias toward smaller N
    // mode 2: bias toward larger N
    // mode 3: uniform random
    int mode = rnd.next(0, 3);
    int N;
    switch (mode) {
        case 0:
            N = 1;
            break;
        case 1:
            // bias toward smaller N (min of two samples)
            N = rnd.wnext(10, -1) + 1;
            break;
        case 2:
            // bias toward larger N (max of two samples)
            N = rnd.wnext(10, 1) + 1;
            break;
        default:
            // uniform between 1 and 10
            N = rnd.next(1, 10);
    }

    println(N);
    return 0;
}
