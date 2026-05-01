#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for diverse N
    double p = rnd.next();
    int N, M;
    if (p < 0.1) {
        // corner small
        N = 1;
    } else if (p < 0.4) {
        // very small
        N = rnd.next(1, 5);
    } else if (p < 0.7) {
        // small-medium
        N = rnd.next(6, 20);
    } else if (p < 0.9) {
        // medium
        N = rnd.next(21, 500);
    } else {
        // large
        N = rnd.next(501, 1000);
    }
    // Hyper-parameter for diverse M (different distribution)
    double q = rnd.next();
    if (q < 0.15) {
        M = 1;
    } else if (q < 0.45) {
        M = rnd.next(1, 10);
    } else if (q < 0.75) {
        M = rnd.next(11, 50);
    } else if (q < 0.95) {
        M = rnd.next(51, 300);
    } else {
        M = rnd.next(301, 1000);
    }
    // Ensure within bounds [1,1000]
    N = max(1, min(1000, N));
    M = max(1, min(1000, M));
    println(N, M);
    return 0;
}
