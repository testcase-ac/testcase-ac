#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Known interesting seeds for Collatz sequences
    vector<int> special = {27, 6171, 77031, 100000};

    // Choose a category for diversity
    int t = rnd.next(0, 4);
    int x;
    if (t == 0) {
        // Minimal edge case
        x = 1;
    } else if (t == 1) {
        // Small random start
        x = rnd.next(2, 20);
    } else if (t == 2) {
        // Medium random start
        x = rnd.next(21, 1000);
    } else if (t == 3) {
        // Large random start
        x = rnd.next(1001, 100000);
    } else {
        // One of the special known cases
        x = rnd.any(special);
    }

    // Output the starting value for C(1)
    println(x);
    return 0;
}
