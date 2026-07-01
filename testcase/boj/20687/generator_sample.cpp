#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomValue(int mode) {
    if (mode == 0) return rnd.next(-10, 10);
    if (mode == 1) return rnd.next(-100000, 100000);
    if (mode == 2) return rnd.any(vector<int>{-100000, -99999, -1, 0, 1, 99999, 100000});
    return rnd.next(-1000, 1000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2;
    } else if (mode <= 4) {
        n = rnd.next(3, 10);
    } else {
        n = rnd.next(11, 30);
    }

    vector<int> a(n);
    if (mode == 0) {
        a[0] = randomValue(rnd.next(0, 2));
    } else if (mode == 1) {
        int x = randomValue(rnd.next(0, 2));
        a[0] = x;
        a[1] = rnd.next(0, 1) ? x : randomValue(rnd.next(0, 2));
    } else if (mode == 2) {
        int lo = rnd.next(-20, 0);
        int hi = rnd.next(0, 20);
        for (int& x : a) x = rnd.next(lo, hi);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? 100000 : -100000);
        int changes = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < changes; ++i) a[rnd.next(0, n - 1)] = randomValue(0);
    } else if (mode == 4) {
        int start = rnd.next(-200, 200);
        int step = rnd.next(-30, 30);
        for (int i = 0; i < n; ++i) a[i] = max(-100000, min(100000, start + step * i));
    } else if (mode == 5) {
        int base = rnd.next(-1000, 1000);
        for (int& x : a) x = base;
        int changes = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < changes; ++i) a[rnd.next(0, n - 1)] = randomValue(rnd.next(0, 1));
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            int sign = (i % 2 == 0) ? 1 : -1;
            a[i] = sign * rnd.next(0, 100000);
        }
    } else {
        for (int& x : a) x = randomValue(rnd.next(0, 3));
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
