#include "testlib.h"

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    ll k;

    if (mode == 0) {
        n = rnd.next(2, 12);
        k = 0;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = 1LL * n * (n - 1) / 2;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        ll maxK = 1LL * n * (n - 1) / 2;
        k = rnd.next(0LL, std::min(10LL, maxK));
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        ll maxK = 1LL * n * (n - 1) / 2;
        k = maxK - rnd.next(0LL, std::min(10LL, maxK));
    } else if (mode == 4) {
        n = rnd.next(2, 80);
        ll maxK = 1LL * n * (n - 1) / 2;
        k = rnd.next(0LL, maxK);
    } else if (mode == 5) {
        n = rnd.next(100, 600);
        ll maxK = 1LL * n * (n - 1) / 2;
        k = rnd.next(0LL, maxK);
    } else {
        n = rnd.next(4000, 4242);
        ll maxK = 1LL * n * (n - 1) / 2;
        k = rnd.next(0LL, maxK);
    }

    println(n, k);
    return 0;
}
