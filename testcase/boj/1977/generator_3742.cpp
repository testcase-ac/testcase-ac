#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int regime = rnd.next(0, 3);
    int M, N;
    if (regime == 0) {
        // No perfect squares in [M, N]
        int k = rnd.next(1, 99);
        int M0 = k * k + 1;
        int N0 = min((k + 1) * (k + 1) - 1, 10000);
        M = M0;
        N = N0;
    } else if (regime == 1) {
        // Exactly one perfect square
        int k = rnd.next(1, 100);
        int sq = k * k;
        M = sq;
        N = sq;
    } else if (regime == 2) {
        // Multiple perfect squares in [M, N]
        int len = rnd.next(2, 5);
        int k_start_max = 100 - (len - 1);
        int k_start = rnd.next(1, k_start_max);
        int min_square = k_start * k_start;
        int max_square = (k_start + len - 1) * (k_start + len - 1);
        int d1max = min(5, min_square - 1);
        int d1 = rnd.next(0, d1max);
        M = min_square - d1;
        int d2max = min(5, 10000 - max_square);
        int d2 = rnd.next(0, d2max);
        N = max_square + d2;
    } else {
        // Generic random interval
        M = rnd.next(1, 10000);
        N = rnd.next(M, 10000);
    }

    println(M);
    println(N);
    return 0;
}
