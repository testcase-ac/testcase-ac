#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to choose between small, large, or random middle cases
    double p = rnd.next();
    int N;
    if (p < 0.2) {
        // smallest allowed
        N = 1000;
    } else if (p > 0.8) {
        // largest allowed
        N = 10000000;
    } else {
        // a random multiple of 1000 between 2000 and 9999000
        int k = rnd.next(2, 9999);
        N = k * 1000;
    }

    // Output a single test case
    println(N);
    return 0;
}
