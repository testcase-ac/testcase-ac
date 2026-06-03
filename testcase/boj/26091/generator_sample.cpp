#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    long long m = rnd.next(1LL, LIM);
    vector<long long> a(n);

    if (mode == 0) {
        n = rnd.next(1, 3);
        a.resize(n);
        m = rnd.any(vector<long long>{1, 2, 10, LIM});
        for (long long& x : a) x = rnd.next(1LL, LIM);
    } else if (mode == 1) {
        m = rnd.next(2LL, LIM);
        long long hi = max(1LL, (m - 1) / 2);
        for (long long& x : a) x = rnd.next(1LL, hi);
    } else if (mode == 2) {
        m = rnd.next(1LL, LIM);
        long long lo = max(1LL, (m + 1) / 2);
        for (long long& x : a) x = rnd.next(lo, LIM);
    } else if (mode == 3) {
        m = rnd.next(2LL, LIM);
        long long lowHi = max(1LL, m / 2);
        for (int i = 0; i < n; i += 2) {
            long long x = rnd.next(1LL, lowHi);
            long long y = rnd.next(max(1LL, m - x), LIM);
            a[i] = x;
            if (i + 1 < n) a[i + 1] = y;
        }
    } else if (mode == 4) {
        m = rnd.next(2LL, LIM);
        long long base = rnd.next(1LL, LIM);
        long long near = min(LIM, max(1LL, m - base));
        vector<long long> pool = {1, base, near, m / 2, min(LIM, m)};
        for (long long& x : pool) x = min(LIM, max(1LL, x));
        for (long long& x : a) x = rnd.any(pool);
    } else {
        m = rnd.next(1LL, LIM);
        long long spread = rnd.next(0LL, 30LL);
        long long center = rnd.next(1LL, LIM);
        if (rnd.next(0, 1) == 1) center = max(1LL, min(LIM, m - center));
        long long lo = max(1LL, center - spread);
        long long hi = min(LIM, center + spread);
        for (long long& x : a) x = rnd.next(lo, hi);
    }

    shuffle(a.begin(), a.end());

    println(n, m);
    println(a);

    return 0;
}
