#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    long long k;

    if (mode == 0) {
        n = rnd.next(2, 8);
        k = 0;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = 1LL * n * (n - 1) / 2;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        long long maxPairs = 1LL * n * (n - 1) / 2;
        k = rnd.any(std::vector<long long>{1, maxPairs - 1});
    } else if (mode == 3) {
        n = rnd.next(3, 80);
        int t = rnd.next(1, n - 1);
        long long base = 1LL * t * (t - 1) / 2;
        long long maxPairs = 1LL * n * (n - 1) / 2;
        k = std::min(maxPairs, base + rnd.next(-1, 1));
        if (k < 0) k = 0;
    } else if (mode == 4) {
        n = rnd.next(2, 200);
        long long maxPairs = 1LL * n * (n - 1) / 2;
        k = rnd.next(0LL, maxPairs);
    } else if (mode == 5) {
        n = rnd.next(500, 2000);
        long long maxPairs = 1LL * n * (n - 1) / 2;
        k = rnd.next(0LL, maxPairs);
    } else if (mode == 6) {
        n = 2000;
        long long maxPairs = 1LL * n * (n - 1) / 2;
        k = rnd.next(maxPairs - 2000, maxPairs);
    } else {
        n = 2000;
        k = rnd.next(0LL, 2000LL);
    }

    println(n, k);
    return 0;
}
