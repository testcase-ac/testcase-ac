#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 60);
    vector<long long> a(n);

    if (mode == 0) {
        long long cur = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 8LL);
            a[i] = cur;
        }
    } else if (mode == 1) {
        long long cur = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0LL, min(1000000LL, cur - 1));
            a[i] = cur;
        }
    } else if (mode == 2) {
        long long low = rnd.next(1LL, 30LL);
        long long high = rnd.next(500000000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? low + rnd.next(0LL, 10LL) : high - rnd.next(0LL, 10LL));
        }
    } else if (mode == 3) {
        int distinct = rnd.next(1, min(n, 8));
        vector<long long> values;
        for (int i = 0; i < distinct; ++i) {
            values.push_back(rnd.next(1LL, 100LL));
        }
        sort(values.begin(), values.end());
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(values);
        }
    } else if (mode == 4) {
        long long record = rnd.next(1LL, 20LL);
        int i = 0;
        while (i < n) {
            a[i++] = record;
            int tail = rnd.next(0, min(8, n - i));
            for (int j = 0; j < tail; ++j) {
                a[i++] = rnd.next(1LL, record);
            }
            record = min(1000000000LL, record + rnd.next(1LL, 30LL));
        }
    } else if (mode == 5) {
        long long base = rnd.next(1LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            a[i] = base;
        }
    } else {
        long long lo = rnd.next(1LL, 1000LL);
        long long hi = rnd.next(lo, min(1000000000LL, lo + rnd.next(0LL, 100000LL)));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
        if (rnd.next(0, 1)) {
            shuffle(a.begin(), a.end());
        }
    }

    println(n);
    println(a);

    return 0;
}
