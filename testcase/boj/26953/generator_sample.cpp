#include "testlib.h"
#include <vector>

using ll = long long;
using std::vector;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxM = 200000;
    const ll maxB = 1000000000000LL;

    int mode = rnd.next(0, 8);
    int M;
    ll b;

    if (mode == 0) {
        M = rnd.next(2, 20);
        b = rnd.next(0LL, 200LL);
    } else if (mode == 1) {
        M = rnd.next(2, 200);
        b = 0;
    } else if (mode == 2) {
        M = rnd.next(2, 1000);
        int factor = rnd.next(1, M);
        b = 1LL * factor * rnd.next(0, 1000000);
    } else if (mode == 3) {
        M = rnd.next(2, 5000);
        b = rnd.next(0LL, 1LL * M * M);
    } else if (mode == 4) {
        M = rnd.next(maxM - 1000, maxM);
        b = rnd.next(0LL, 1000000LL);
    } else if (mode == 5) {
        M = rnd.next(maxM - 1000, maxM);
        b = maxB - rnd.next(0LL, 1000000LL);
    } else if (mode == 6) {
        M = rnd.next(2, maxM);
        vector<ll> bases = {1LL, 2LL, 3LL, 5LL, 10LL, 100LL, 1000LL, 1000000LL};
        ll base = rnd.any(bases);
        b = base * rnd.next(0LL, maxB / base);
    } else if (mode == 7) {
        vector<int> sizes = {2, 3, 4, 5, 10, 100, 1000, 10000, 100000, maxM};
        M = rnd.any(sizes);
        b = rnd.next(0LL, maxB);
    } else {
        M = rnd.next(2, maxM);
        b = rnd.next(0LL, maxB);
    }

    println(M, b);
    return 0;
}
