#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to pick N in small, medium, or large range
    double p = rnd.next();  // in [0,1)
    int N;
    if (p < 0.1) {
        // Occasionally generate near-maximum cases
        N = rnd.next(90, 100);
    } else if (p < 0.3) {
        // Some medium-size cases
        N = rnd.next(11, 50);
    } else {
        // Mostly small, hand-checkable cases
        N = rnd.next(1, 10);
    }

    // Output the single integer N
    println(N);
    return 0;
}
