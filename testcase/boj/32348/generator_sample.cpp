#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long bounded(long long x) {
    return max(1LL, min(1000000000LL, x));
}

vector<long long> makeValues(int n, int mode) {
    vector<long long> values(n);

    if (mode == 0) {
        long long base = rnd.next(1, 30);
        for (long long& x : values) x = bounded(base + rnd.next(-2, 2));
    } else if (mode == 1) {
        vector<long long> choices = {1, 2, 3, 999999998LL, 999999999LL, 1000000000LL};
        for (long long& x : values) x = rnd.any(choices);
    } else if (mode == 2) {
        long long lo = rnd.next(1, 50);
        long long hi = rnd.next(50, 200);
        for (long long& x : values) x = rnd.next(lo, hi);
        sort(values.begin(), values.end());
    } else if (mode == 3) {
        long long start = rnd.next(1, 40);
        long long step = rnd.next(1, 15);
        for (int i = 0; i < n; ++i) values[i] = bounded(start + step * i + rnd.next(0, 3));
    } else {
        long long pivot = rnd.next(20, 100);
        for (long long& x : values) {
            if (rnd.next(0, 2) == 0) {
                x = bounded(pivot + rnd.next(-5, 5));
            } else {
                x = rnd.next(1, 200);
            }
        }
    }

    if (rnd.next(0, 1) == 0) shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 10);
        m = rnd.next(1, min(3, n));
    } else if (mode == 2) {
        n = rnd.next(1, 4);
        m = rnd.next(8, 18);
    } else if (mode == 3) {
        n = m = rnd.next(2, 12);
    } else if (mode == 4) {
        n = rnd.next(10, 25);
        m = rnd.next(10, 25);
    }

    vector<long long> a = makeValues(n, rnd.next(0, 4));
    vector<long long> b = makeValues(m, rnd.next(0, 4));

    if (mode == 5) {
        long long target = rnd.next(30, 120);
        for (long long& x : a) x = rnd.next(1LL, target);
        for (long long& x : b) x = bounded(target - rnd.next(0, 20));
        shuffle(a.begin(), a.end());
        shuffle(b.begin(), b.end());
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
