#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We generate N with different regimes for diversity:
    // - 10% chance of the absolute minimum N=1
    // - 20% chance of small N in [2,10]
    // - 30% chance of medium N in [11,100]
    // - 25% chance of larger N in [101,500]
    // - 13% chance of near-maximum N in [501,999]
    // - 2% chance of the absolute maximum N=1000
    double p = rnd.next();
    int N;
    if (p < 0.10) {
        N = 1;
    } else if (p < 0.30) {
        N = rnd.next(2, 10);
    } else if (p < 0.60) {
        N = rnd.next(11, 100);
    } else if (p < 0.85) {
        N = rnd.next(101, 500);
    } else if (p < 0.98) {
        N = rnd.next(501, 999);
    } else {
        N = 1000;
    }

    // Output a single integer N
    println(N);
    return 0;
}
