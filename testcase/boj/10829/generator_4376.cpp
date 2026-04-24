#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose scale of N for diversity
    int scale = rnd.next(0, 3);
    long long N;
    if (scale == 0) {
        // very small, easy hand-check
        N = rnd.next(1, 7);
    } else if (scale == 1) {
        // small
        N = rnd.next(8, 100);
    } else if (scale == 2) {
        // medium
        N = rnd.next(101, 10000);
    } else {
        // large, near upper constraints
        const long long MAXN = 100000000000000LL;
        if (rnd.next(0,1) == 0) {
            // sample from the upper half
            N = rnd.next(MAXN / 2, MAXN);
        } else {
            // sample a moderately large value
            N = rnd.next(10001, 1000000);
        }
    }

    // Output the single test case
    println(N);
    return 0;
}
