#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter for N: small, medium, large, very large
    double pN = rnd.next();
    int N;
    if (pN < 0.2) {
        N = rnd.next(1, 10);
    } else if (pN < 0.6) {
        N = rnd.next(11, 50);
    } else if (pN < 0.9) {
        N = rnd.next(51, 100);
    } else {
        N = rnd.next(101, 200);
    }
    // Hyperparameter for K: mix of relative-to-N and independent ranges
    double pK = rnd.next();
    int K;
    if (pK < 0.25) {
        // small relative to N
        K = rnd.next(1, min(N, 10));
    } else if (pK < 0.5) {
        // small independent
        K = rnd.next(1, 10);
    } else if (pK < 0.75) {
        // medium independent
        K = rnd.next(11, 50);
    } else {
        // large independent
        K = rnd.next(51, 200);
    }
    // Output the single test case: two integers N and K
    println(N, K);
    return 0;
}
