#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter to choose range size for diversity
    double phase = rnd.next(); // in [0,1)
    int maxv;
    if (phase < 0.33) {
        maxv = 5;   // small case
    } else if (phase < 0.66) {
        maxv = 10;  // medium case
    } else {
        maxv = 20;  // larger but still hand-checkable
    }
    // Sample N and K from 1 to maxv
    int N = rnd.next(1, maxv);
    int K = rnd.next(1, maxv);
    // Occasionally force edge values
    if (rnd.next() < 0.1) N = 1;
    if (rnd.next() < 0.1) K = 1;
    if (rnd.next() < 0.1) N = maxv;
    if (rnd.next() < 0.1) K = maxv;
    // Output the test case
    println(N, K);
    return 0;
}
