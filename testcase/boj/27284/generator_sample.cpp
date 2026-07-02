#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

long long smallValue(int limit) {
    return rnd.next(1, limit);
}

long long sometimesLarge(long long value) {
    if (rnd.next(8) == 0) return 1000000000LL;
    if (rnd.next(8) == 0) return 1000000000LL - rnd.next(0, 20);
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 24);
    int m = rnd.next(1, min(10, n));
    int mode = rnd.next(6);

    vector<pair<long long, long long>> a(n);
    int heightLimit = rnd.next(2, 12);
    int strengthLimit = rnd.next(2, 30);

    for (int i = 0; i < n; ++i) {
        long long h;
        if (mode == 0) {
            h = rnd.next(1, heightLimit);
        } else if (mode == 1) {
            h = i + 1;
        } else if (mode == 2) {
            h = n - i;
        } else if (mode == 3) {
            h = (i % 2 == 0 ? heightLimit : rnd.next(1, heightLimit));
        } else if (mode == 4) {
            h = 1 + min(i, n - 1 - i);
        } else {
            h = rnd.next(1, 4);
            if (rnd.next(5) == 0) h = 1000000000LL - rnd.next(0, 5);
        }

        long long s;
        if (mode == 1) {
            s = n - i + rnd.next(0, 3);
        } else if (mode == 2) {
            s = i + 1 + rnd.next(0, 3);
        } else if (mode == 3) {
            s = (i % 2 == 0 ? strengthLimit : rnd.next(1, strengthLimit));
        } else {
            s = smallValue(strengthLimit);
        }

        a[i] = {sometimesLarge(h), sometimesLarge(s)};
    }

    if (mode == 4 && rnd.next(2) == 0) {
        reverse(a.begin(), a.end());
    }

    println(n, m);
    for (auto [h, s] : a) {
        println(h, s);
    }

    return 0;
}
