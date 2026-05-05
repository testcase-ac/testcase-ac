#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    double p = rnd.next(); // in [0,1)

    // Bias towards some interesting sizes while keeping variety
    if (p < 0.05) {
        // Smallest edge case
        N = 2;
    } else if (p < 0.15) {
        // Very small boards
        N = rnd.next(3, 5);
    } else if (p < 0.40) {
        // Small/medium boards
        N = rnd.next(6, 20);
    } else if (p < 0.90) {
        // Medium/large boards
        N = rnd.next(21, 49);
    } else{
        // Larger boards
        N = 50;
    }

    println(N);
    return 0;
}
