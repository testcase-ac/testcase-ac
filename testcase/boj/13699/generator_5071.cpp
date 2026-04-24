#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    double p = rnd.next();
    int n;
    if (p < 0.05) {
        // edge case: smallest
        n = 0;
    } else if (p < 0.10) {
        // edge case: largest
        n = 35;
    } else if (p < 0.40) {
        // small n
        n = rnd.next(0, 5);
    } else if (p < 0.70) {
        // medium n
        n = rnd.next(6, 20);
    } else if (p < 0.90) {
        // larger but not extreme
        n = rnd.next(21, 30);
    } else {
        // completely random
        n = rnd.next(0, 35);
    }
    println(n);
    return 0;
}
