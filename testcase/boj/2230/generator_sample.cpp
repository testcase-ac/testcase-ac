#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_A = -1000000000LL;
    const long long MAX_A = 1000000000LL;

    int mode = rnd.next(0, 5);
    int n = 1;
    long long m = 0;
    vector<long long> a;

    if (mode == 0) {
        n = 1;
        m = 0;
        a.push_back(rnd.next(MIN_A, MAX_A));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        long long value = rnd.next(-20LL, 20LL);
        m = 0;
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = rnd.next(1LL, 50LL);
        long long lo = rnd.next(-100LL, 100LL - m);
        a.push_back(lo);
        a.push_back(lo + m);
        for (int i = 2; i < n; ++i) {
            a.push_back(rnd.next(lo, lo + m));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        long long lo = rnd.next(-1000000000LL, -999999900LL);
        long long hi = rnd.next(999999900LL, 1000000000LL);
        m = rnd.next(1000000000LL, 2000000000LL);
        a.push_back(lo);
        a.push_back(hi);
        for (int i = 2; i < n; ++i) {
            a.push_back(rnd.next(-1000LL, 1000LL));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        long long lo = rnd.next(-1000LL, 900LL);
        long long span = rnd.next(1LL, 100LL);
        long long hi = lo + span;
        m = rnd.next(1LL, span);
        a.push_back(lo);
        a.push_back(hi);
        for (int i = 2; i < n; ++i) {
            long long cluster = rnd.next(0, 1) == 0 ? lo : hi;
            a.push_back(cluster + rnd.next(-3LL, 3LL));
        }
    } else {
        n = rnd.next(2, 18);
        long long lo = rnd.next(-5000LL, 4000LL);
        long long hi = rnd.next(lo + 1, lo + 1000);
        m = rnd.next(1LL, hi - lo);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
        a[0] = lo;
        a[1] = hi;
    }

    shuffle(a.begin(), a.end());

    println(n, m);
    for (long long x : a) {
        println(x);
    }

    return 0;
}
