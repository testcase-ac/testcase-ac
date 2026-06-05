#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(4, 12);
        a.assign(n, 0);
    } else if (mode == 1) {
        n = rnd.next(4, 20);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 1);
    } else if (mode == 2) {
        n = rnd.next(4, 25);
        vector<int> values = {0, 1, 2, 3, 5, 7, 11, 13};
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.any(values);
    } else if (mode == 3) {
        n = rnd.next(4, 30);
        int lo = rnd.next(0, 40);
        int hi = rnd.next(lo, min(2000, lo + rnd.next(0, 80)));
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(lo, hi);
    } else if (mode == 4) {
        n = rnd.next(4, 35);
        vector<int> values = {0, 1, 1999, 2000};
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.any(values);
    } else if (mode == 5) {
        n = rnd.next(4, 50);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? rnd.next(0, 5) : rnd.next(1000, 2000));
    } else if (mode == 6) {
        n = rnd.next(4, 80);
        a.resize(n);
        int base = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) a[i] = (base + i * rnd.next(0, 3)) % 2001;
    } else {
        n = rnd.next(100, 180);
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 2000);
    }

    println(n);
    println(a);

    return 0;
}
