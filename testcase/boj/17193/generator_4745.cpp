#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Maximum N for small, hand-checkable cases
    const int MAXN = 10;

    // Hyper-parameter: choose N in three modes
    int N;
    double modeN = rnd.next();
    if (modeN < 0.2) {
        // minimal size
        N = 2;
    } else if (modeN < 0.4) {
        // maximal small size
        N = MAXN;
    } else {
        // random intermediate
        N = rnd.next(2, MAXN);
    }

    // Hyper-parameter: choose K in three modes
    int K;
    double modeK = rnd.next();
    if (modeK < 0.3) {
        // smallest non-trivial grouping
        K = 2;
    } else if (modeK < 0.6) {
        // as many groups as cows
        K = N;
    } else {
        // random between 2 and N
        K = rnd.next(2, N);
    }

    // Output the test case: N cows and K groups
    println(N, K);
    return 0;
}
