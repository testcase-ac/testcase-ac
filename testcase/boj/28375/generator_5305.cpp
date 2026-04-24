#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Use a few modes for diversity
    double p = rnd.next();
    int n;
    if (p < 0.2) {
        // Small for hand-checking
        n = rnd.next(1, 20);
    } else if (p < 0.4) {
        // Medium size
        n = rnd.next(21, 1000000);
    } else if (p < 0.6) {
        // Powers of ten minus one, plus one edge
        vector<int> specials = {9, 99, 999, 9999, 99999, 999999, 9999999, 99999999, 999999999, 1000000000};
        n = rnd.any(specials);
    } else if (p < 0.8) {
        // Large range skewed to high
        n = rnd.wnext(1000000000, +2) + 1;  // tends toward large values
    } else {
        // Uniform full range
        n = rnd.next(1, 1000000000);
    }

    println(n);
    return 0;
}
