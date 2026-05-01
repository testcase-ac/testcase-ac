#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with small/medium/large bias
    int N;
    double q = rnd.next();
    if (q < 0.3) {
        N = rnd.next(2, 10);
    } else if (q < 0.7) {
        N = rnd.next(11, 1000);
    } else {
        N = rnd.next(1001, 100000);
    }
    // Choose M to cover edge and typical cases
    int M;
    double p = rnd.next();
    if (p < 0.25) {
        M = 2;
    } else if (p < 0.5) {
        M = N;
    } else if (p < 0.75) {
        int mid = N / 2;
        int lo = max(2, mid - 3);
        int hi = min(N, mid + 3);
        M = rnd.next(lo, hi);
    } else {
        M = rnd.next(2, N);
    }
    // Output the single test case
    println(N, M);
    return 0;
}
