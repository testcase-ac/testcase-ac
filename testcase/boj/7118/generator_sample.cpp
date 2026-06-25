#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int clampToLimit(long long x) {
    return static_cast<int>(min(999999999LL, max(1LL, x)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int p = 2;
    int n = 1;

    if (mode == 0) {
        p = rnd.next(2, 60);
        n = rnd.next(1, 60);
    } else if (mode == 1) {
        vector<int> smallP = {2, 3, 4, 5, 8, 9, 10, 17, 26, 80};
        p = rnd.any(smallP);
        n = rnd.next(1, 200);
    } else if (mode == 2) {
        int k = rnd.next(1, 28);
        p = (1 << k) - 1;
        if (p < 2) p = 3;
        n = 2 * rnd.next(1, 200000);
    } else if (mode == 3) {
        int k = rnd.next(1, 18);
        long long pow3 = 1;
        for (int i = 0; i < k; ++i) pow3 *= 3;
        p = clampToLimit(pow3 - 1);
        if (p < 2) p = 2;
        n = 2 * rnd.next(1, 200000);
    } else if (mode == 4) {
        p = rnd.next(2, 999999999);
        n = rnd.next(1, 999999999);
        if (rnd.next(0, 1)) n -= n % 2;
        if (n < 1) n = 2;
    } else if (mode == 5) {
        p = rnd.next(2, 999999999);
        n = 1;
        for (int i = 0; i < rnd.next(0, 18); ++i) n = clampToLimit(1LL * n * 3);
        n = clampToLimit(1LL * n * rnd.next(1, 40));
    } else {
        p = rnd.next(999999000, 999999999);
        n = rnd.next(999999000, 999999999);
    }

    println(p, n);
    return 0;
}
