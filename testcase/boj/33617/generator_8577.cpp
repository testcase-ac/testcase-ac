#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    double p = rnd.next(); // in [0,1)

    // Bias towards some interesting sizes while keeping variety
    if (p < 0.20) {
        // Smallest edge case
        N = 2;
    } else if (p < 0.40) {
        // Very small boards
        N = rnd.next(3, 5);
    } else if (p < 0.75) {
        // Small/medium boards
        N = rnd.next(6, 15);
    } else if (p < 0.90) {
        // Medium/large boards
        N = rnd.next(16, 30);
    } else if (p < 0.98) {
        // Larger boards
        N = rnd.next(31, 49);
    } else {
        // Maximum size edge case
        N = 50;
    }

    println(N);
    return 0;
}
