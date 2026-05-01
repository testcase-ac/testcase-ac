#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with varied sizes: small, medium, large
    double p = rnd.next();
    int N;
    if (p < 0.3) {
        N = rnd.next(2, 10);
    } else if (p < 0.8) {
        N = rnd.next(11, 30);
    } else {
        N = rnd.next(31, 50);
    }
    // Compute sizes of Fibonacci trees up to N
    vector<long long> fibSz(N + 1);
    fibSz[0] = fibSz[1] = 1;
    for (int i = 2; i <= N; i++) {
        fibSz[i] = 1 + fibSz[i - 1] + fibSz[i - 2];
    }
    // Maximum label is min(tree size, 1e9)
    long long posMax = min(fibSz[N], 1000000000LL);
    int hi = (int)posMax;  // hi >= 3 since N >= 2
    // Use weighted next to bias endpoints or uniform
    int tA = rnd.next(-2, 2);
    int tB = rnd.next(-2, 2);
    long long a = rnd.wnext(hi, tA) + 1;
    long long b = rnd.wnext(hi, tB) + 1;
    // Ensure distinct positions
    while (b == a) {
        b = rnd.wnext(hi, tB) + 1;
    }
    // Output the single test case
    println(N, a, b);
    return 0;
}
