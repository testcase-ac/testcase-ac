#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Some specially interesting n (boundaries, small values, near powers of 2, etc.)
    vector<int> special = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        16, 31, 32, 63, 64, 99, 100, 127, 128,
        255, 256, 511, 512, 767, 768, 900, 950, 998, 999
    };

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        // Purely from special set
        n = rnd.any(special);
    } else if (mode == 1) {
        // Very small n
        n = rnd.next(0, 20);
    } else if (mode == 2) {
        // Small / medium n
        n = rnd.next(21, 200);
    } else if (mode == 3) {
        // Medium / large n
        n = rnd.next(201, 800);
    } else {
        // Very large n
        n = rnd.next(801, 999);
    }

    println(n);

    return 0;
}
