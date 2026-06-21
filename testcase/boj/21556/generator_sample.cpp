#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_A = 1000000000LL;
    int mode = rnd.next(0, 6);
    int n;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(2, 12);
        long long value = rnd.any(vector<long long>{1LL, 2LL, 7LL, MAX_A});
        a.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(3, 30);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1) == 0 ? 1LL : MAX_A);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 50);
        long long center = rnd.next(1LL, MAX_A);
        long long spread = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) {
            long long lo = max(1LL, center - spread);
            long long hi = min(MAX_A, center + spread);
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 60);
        long long start = rnd.next(1LL, 1000LL);
        long long step = rnd.next(0LL, 1000000LL);
        for (int i = 0; i < n; ++i) {
            long long value = min(MAX_A, start + step * i);
            a.push_back(value);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 120);
        int buckets = rnd.next(2, 8);
        vector<long long> values;
        for (int i = 0; i < buckets; ++i) {
            values.push_back(rnd.next(1LL, MAX_A));
        }
        values.push_back(1LL);
        values.push_back(MAX_A);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(values));
        }
    } else if (mode == 5) {
        n = rnd.next(1000, 5000);
        long long lo = rnd.next(1LL, 1000000LL);
        long long hi = rnd.next(MAX_A - 1000000LL, MAX_A);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 3) == 0 ? rnd.next(lo, min(MAX_A, lo + 1000)) : rnd.next(max(1LL, hi - 1000), hi));
        }
    } else {
        n = rnd.next(2, 80);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1LL, MAX_A));
        }
    }

    if (rnd.next(0, 1) == 1) {
        sort(a.begin(), a.end());
        if (rnd.next(0, 1) == 1) {
            reverse(a.begin(), a.end());
        }
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
