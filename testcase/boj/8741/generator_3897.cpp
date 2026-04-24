#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: pick different k-ranges for diversity
    int mode = rnd.next(0, 2);
    int k;
    if (mode == 0) {
        // smallest edge case
        k = 1;
    } else if (mode == 1) {
        // small k for easy hand-check
        k = rnd.next(2, 5);
    } else {
        // moderate k to test bit growth
        k = rnd.next(6, 20);
    }

    // Output k
    println(k);

    return 0;
}
