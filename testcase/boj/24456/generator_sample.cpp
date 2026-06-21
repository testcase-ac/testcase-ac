#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    long long k;

    if (mode == 0) {
        int side = rnd.next(1, 25);
        n = side;
        m = side;
        k = rnd.next(0LL, min(1LL * n * m, 2LL * side + 10));
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        m = n + rnd.next(0, 8);
        if (m > 10000) m = 10000;
        k = rnd.next(0LL, min(1LL * n * m, 20LL));
    } else if (mode == 2) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 80);
        if (rnd.next(0, 1)) swap(n, m);
        k = rnd.next(0LL, min(1LL * n * m, 80LL));
    } else if (mode == 3) {
        n = rnd.next(2, 40);
        m = rnd.next(2, 40);
        k = 0;
    } else if (mode == 4) {
        n = rnd.next(1, 60);
        m = rnd.next(1, 60);
        int oldDiff = abs(n - m);
        k = rnd.next(0LL, min(1LL * n * m, 1LL * oldDiff + 12));
    } else if (mode == 5) {
        vector<int> values = {1, 2, 3, 4, 5, 10, 99, 100, 999, 1000, 9999, 10000};
        n = rnd.any(values);
        m = rnd.any(values);
        long long product = 1LL * n * m;
        vector<long long> candidates = {0, 1, min(product, 10LL), min(product, product / 2), product};
        k = rnd.any(candidates);
    } else {
        n = rnd.next(9000, 10000);
        m = rnd.next(9000, 10000);
        long long product = 1LL * n * m;
        long long cap = min(product, 200000LL);
        k = rnd.next(product - cap, product);
    }

    println(n, m, k);
    return 0;
}
