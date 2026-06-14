#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

const int64 kMaxA = 1000000000000LL;

int64 randomNearLimit() {
    return rnd.next(kMaxA - 2000, kMaxA);
}

int64 randomSmall() {
    return rnd.next(1LL, 200LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<int64> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 1) == 0 ? randomSmall() : randomNearLimit();
        }
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int64 d = rnd.any(vector<int64>{2, 3, 5, 7, 11, 17, 31, 97, 1000003});
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int64 q = rnd.next(1LL, min<int64>(1000, kMaxA / d));
            a[i] = d * q - rnd.next(0, 1);
            if (a[i] < 1) a[i] += d;
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(2, 25);
        int64 base = rnd.next(1LL, 1000000LL);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int64 delta = rnd.next(-3LL, 3LL);
            a[i] = max<int64>(1, base + delta);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        int64 d = rnd.next(2LL, 1000000LL);
        int64 q = kMaxA / d;
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int64 x = d * rnd.next(max<int64>(1, q - 30), q);
            if (rnd.next(0, 1) == 1 && x > 1) --x;
            a[i] = x;
        }
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int64 lo = rnd.next(1LL, 1000LL);
            int64 hi = rnd.next(lo, lo + rnd.next(0LL, 10000LL));
            a[i] = rnd.next(lo, min<int64>(hi, kMaxA));
        }
    } else {
        n = rnd.next(1, 12);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int64 value = rnd.any(vector<int64>{1, 2, 3, 999999937LL, kMaxA - 1, kMaxA});
            if (rnd.next(0, 2) == 0) value = randomSmall();
            a[i] = value;
        }
    }

    println(n);
    println(a);

    return 0;
}
