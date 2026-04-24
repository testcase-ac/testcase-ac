#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    // We'll generate a small, hand-checkable range [a, b] with b up to 20.
    int maxB = rnd.next(1, 20);
    int a = rnd.next(1, maxB);

    // Choose b with different behaviors:
    // 20% chance b == a (single term),
    // 30% chance small segment of length up to 2,
    // otherwise full random segment up to maxB.
    double p = rnd.next();
    int b;
    if (p < 0.2) {
        b = a;
    } else if (p < 0.5) {
        b = rnd.next(a, min(a + 2, maxB));
    } else {
        b = rnd.next(a, maxB);
    }

    // Output the single test case
    println(a, b);
    return 0;
}
