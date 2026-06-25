#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using int64 = long long;

int64 capToLimit(__int128 value) {
    const int64 limit = 1000000000000000LL;
    if (value > limit) return limit;
    return static_cast<int64>(value);
}

int64 maxReachable(int k, int a) {
    __int128 sum = ((__int128)1 << k) - 1;
    return capToLimit(sum * a);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 7);
    int k = 1;
    int a = 1;
    int64 n = 1;

    if (mode == 0) {
        k = rnd.next(1, 8);
        a = rnd.next(1, 8);
        n = rnd.next(1LL, maxReachable(k, a));
    } else if (mode == 1) {
        k = rnd.next(1, 40);
        a = rnd.next(1, 5);
        int bit = rnd.next(0, min(k - 1, 39));
        int64 base = 1LL << bit;
        int64 delta = rnd.next(-3LL, 3LL);
        n = max(1LL, min(1000000000000000LL, base + delta));
    } else if (mode == 2) {
        k = rnd.next(30, 40);
        a = rnd.next(1, 20);
        vector<int> bits;
        int take = rnd.next(1, min(k, 8));
        for (int i = 0; i < k; ++i) bits.push_back(i);
        shuffle(bits.begin(), bits.end());
        __int128 sum = 0;
        for (int i = 0; i < take; ++i) sum += (__int128)rnd.next(1, a) * ((__int128)1 << bits[i]);
        n = max(1LL, capToLimit(sum));
    } else if (mode == 3) {
        k = rnd.next(1, 40);
        a = rnd.next(1, 1000000);
        int64 reach = maxReachable(k, min(a, 1000));
        n = rnd.next(1LL, reach);
    } else if (mode == 4) {
        k = rnd.next(1, 40);
        a = rnd.next(1, 1000000);
        n = rnd.next(999999999000000LL, 1000000000000000LL);
    } else if (mode == 5) {
        k = rnd.next(1, 20);
        a = rnd.next(1, 1000000);
        int64 reach = maxReachable(k, a);
        n = rnd.next(max(1LL, reach - 1000), reach);
    } else if (mode == 6) {
        k = rnd.next(1, 12);
        a = rnd.next(1, 12);
        int64 reach = maxReachable(k, a);
        n = min(1000000000000000LL, reach + rnd.next(1LL, 1000LL));
    } else {
        k = rnd.any(vector<int>{1, 2, 3, 10, 20, 40});
        a = rnd.any(vector<int>{1, 2, 3, 1048573, 1000000});
        n = rnd.any(vector<int64>{1LL, 2LL, 3LL, 58LL, 1000LL, 1048573LL, 1000000000000000LL});
    }

    println(k, a, n);
    return 0;
}
