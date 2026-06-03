#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

long long smallValue(int lo, int hi) {
    return rnd.next(lo, hi);
}

long long largeValue(int sign) {
    long long value = rnd.next(900000000, 1000000000);
    return sign < 0 ? -value : value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(1, 6);
        a.resize(n);
        for (long long& x : a) x = smallValue(-8, 8);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        a.resize(n);
        for (long long& x : a) x = -smallValue(1, 100);
    } else if (mode == 2) {
        n = rnd.next(6, 24);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int sign = (i % 2 == 0 ? 1 : -1);
            a[i] = sign * smallValue(1, 30);
        }
    } else if (mode == 3) {
        n = rnd.next(8, 30);
        a.assign(n, 0);
        int positives = rnd.next(1, min(5, n));
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < positives; ++i) a[pos[i]] = smallValue(1, 50);
        for (int i = positives; i < n; ++i) a[pos[i]] = -smallValue(0, 20);
    } else if (mode == 4) {
        n = rnd.next(10, 36);
        a.resize(n);
        int block = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            bool positiveBlock = ((i / block) % 2 == 0);
            a[i] = positiveBlock ? smallValue(1, 25) : -smallValue(1, 35);
        }
    } else if (mode == 5) {
        n = rnd.next(3, 18);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int sign = rnd.next(0, 1) == 0 ? -1 : 1;
            a[i] = largeValue(sign);
        }
    } else if (mode == 6) {
        n = rnd.next(20, 60);
        a.resize(n);
        long long current = smallValue(-10, 10);
        for (int i = 0; i < n; ++i) {
            current += smallValue(-5, 5);
            current = max(-40LL, min(40LL, current));
            a[i] = current;
        }
    } else {
        n = rnd.next(40, 120);
        a.resize(n);
        for (long long& x : a) {
            int bucket = rnd.next(0, 9);
            if (bucket < 2) x = 0;
            else if (bucket < 6) x = smallValue(-100, 100);
            else x = rnd.next(0, 1) == 0 ? largeValue(-1) : largeValue(1);
        }
    }

    println(n);
    println(a);

    return 0;
}
