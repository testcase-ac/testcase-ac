#include "testlib.h"

#include <algorithm>
#include <cstdint>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxX = 1000000000000000000LL;

    int mode = rnd.next(0, 7);
    int N;
    int K;
    long long X;

    if (mode == 0) {
        N = 1;
        K = rnd.next(1, 20);
        X = rnd.next(1LL, 5LL);
    } else if (mode == 1) {
        N = rnd.next(2, 12);
        K = rnd.next(1, 2 * N - 2);
        X = rnd.next(1LL, 20LL);
    } else if (mode == 2) {
        N = rnd.next(2, 20);
        K = 2 * N - 1;
        X = rnd.next(1LL, 4LL);
    } else if (mode == 3) {
        N = rnd.next(2, 20);
        int extraPairs = rnd.next(0, 25);
        K = 2 * N - 1 + 2 * extraPairs;
        X = rnd.next(1LL, 1000000LL);
    } else if (mode == 4) {
        N = rnd.next(2, 20);
        int extraPairs = rnd.next(0, 25);
        K = 2 * N + 2 * extraPairs;
        X = rnd.next(1LL, 1000000LL);
    } else if (mode == 5) {
        K = rnd.next(1, 100000);
        N = rnd.next(max(1, (K + 3) / 2), 100000);
        X = rnd.next(1LL, maxX);
    } else if (mode == 6) {
        N = rnd.next(90000, 100000);
        K = rnd.next(90000, 100000);
        X = rnd.next(maxX - 1000000LL, maxX);
    } else {
        N = rnd.next(1, 100000);
        K = rnd.next(1, 100000);
        X = rnd.next(1LL, maxX);
    }

    println(N, K, X);
    return 0;
}
