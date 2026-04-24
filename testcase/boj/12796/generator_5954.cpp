#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a category for K to add variability
    int p = rnd.next(1, 100);
    long long K;
    if (p <= 5) {
        // Edge case: minimum
        K = 1;
    } else if (p <= 20) {
        // Small K for trivial cases
        K = rnd.next(1, 20);
    } else if (p <= 40) {
        // Small-medium K
        K = rnd.next(21, 1000);
    } else if (p <= 70) {
        // Medium K
        K = rnd.next(1001, 1000000);
    } else if (p <= 90) {
        // Large random K
        K = rnd.next(1000001, 1000000000);
    } else if (p <= 95) {
        // Power-of-two K
        int t = rnd.next(0, 29);
        K = 1LL << t;
    } else {
        // Near-maximum K
        K = rnd.next(1000000000 - 100, 1000000000);
    }

    println(K);
    return 0;
}
