#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a category for N to expose edge cases and performance limits
    int t = rnd.next(0, 99);
    int N;
    if (t < 10) {
        // Edge case: zero
        N = 0;
    } else if (t < 30) {
        // Small values
        N = rnd.next(1, 10);
    } else if (t < 60) {
        // Moderate values
        N = rnd.next(11, 1000);
    } else if (t < 85) {
        // Larger moderate values
        N = rnd.next(1001, 10000);
    } else if (t < 95) {
        // Large values
        N = rnd.next(10001, 50000);
    } else {
        // Very large values near the upper bound
        N = rnd.next(50001, 100000);
    }

    // Output the single integer N
    println(N);

    return 0;
}
