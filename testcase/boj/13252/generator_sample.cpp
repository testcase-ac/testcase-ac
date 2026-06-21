#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000LL;

    int mode = rnd.next(0, 6);
    long long n;
    int m;
    int k;

    if (mode == 0) {
        n = rnd.next(1LL, 8LL);
        m = rnd.next(1, 6);
        k = rnd.next(1, 8);
    } else if (mode == 1) {
        m = rnd.next(1, 50);
        k = rnd.next(1, 50);
        n = rnd.any(vector<long long>{1LL, 2LL, (long long)m, (long long)m + 1});
        n = min(n, maxN);
    } else if (mode == 2) {
        m = rnd.next(2, 50);
        k = rnd.next(2, 50);
        n = 1;
        int exponent = rnd.next(1, min(k, 12));
        for (int i = 0; i < exponent && n <= maxN / m; ++i) {
            n *= m;
        }
        long long delta = rnd.next(-3LL, 3LL);
        n = max(1LL, min(maxN, n + delta));
    } else if (mode == 3) {
        m = rnd.next(2, 50);
        k = rnd.next(35, 50);
        n = rnd.next(maxN - 1000000LL, maxN);
    } else if (mode == 4) {
        m = rnd.next(1, 3);
        k = rnd.next(1, 50);
        n = rnd.next(1LL, maxN);
    } else if (mode == 5) {
        m = 50;
        k = rnd.next(1, 50);
        n = rnd.next(1LL, 1000000LL);
    } else {
        m = rnd.next(1, 50);
        k = rnd.next(1, 50);
        n = rnd.next(1LL, maxN);
    }

    println(n, m, k);
    return 0;
}
