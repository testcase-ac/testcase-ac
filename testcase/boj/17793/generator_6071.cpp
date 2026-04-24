#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of players n: small, medium, or large
    int nMode = rnd.next(0, 2);
    int n;
    if (nMode == 0) {
        n = rnd.next(2, 10);           // small n
    } else if (nMode == 1) {
        n = rnd.next(11, 30);          // medium n
    } else {
        n = rnd.wnext(49, 2) + 2;      // large n, biased to high values
    }

    // Hyper-parameter for number of lives k: small, medium, or large
    int kMode = rnd.next(0, 2);
    int k;
    if (kMode == 0) {
        k = rnd.next(1, 5);            // small k
    } else if (kMode == 1) {
        k = rnd.next(6, 20);           // medium k
    } else {
        k = rnd.wnext(50, 2) + 1;      // large k, biased to high values
    }

    // Hyper-parameter for coin bias p: low, medium, or high range
    int pMode = rnd.next(0, 2);
    double p;
    if (pMode == 0) {
        p = rnd.next(0.1, 0.3);
    } else if (pMode == 1) {
        p = rnd.next(0.4, 0.6);
    } else {
        p = rnd.next(0.7, 0.9);
    }

    // Output the test case
    printf("%d %d %.6f\n", n, k, p);
    return 0;
}
