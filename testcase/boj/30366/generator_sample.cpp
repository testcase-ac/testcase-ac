#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    long long m;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1LL, 20LL);
        a.resize(n);
        for (long long& x : a) x = rnd.next(1LL, m);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        m = rnd.next(2LL, 100LL);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(1LL, m - 1);
            a[i] = (i % 2 == 0 ? x : m - x);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 40);
        m = rnd.next(3LL, 1000LL);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) a[i] = m;
            else if (i % 3 == 1) a[i] = rnd.next(1LL, max(1LL, m / 4));
            else a[i] = rnd.next(max(1LL, m * 3 / 4), m);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 60);
        m = rnd.next(10LL, 1000000000LL);
        a.resize(n);
        for (long long& x : a) {
            long long low = max(1LL, m - rnd.next(0LL, min(1000LL, m - 1)));
            x = rnd.next(low, m);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 80);
        m = rnd.next(1LL, 1000000000LL);
        a.resize(n);
        long long cap = min(m, 1000000LL);
        for (long long& x : a) x = rnd.next(1LL, cap);
    } else {
        n = rnd.next(1, 50);
        m = rnd.next(1LL, 1000000000LL);
        a.resize(n);
        long long small = max(1LL, min(m, rnd.next(1LL, 50LL)));
        for (long long& x : a) x = rnd.next(1LL, small);
    }

    println(n, m);
    println(a);
    return 0;
}
