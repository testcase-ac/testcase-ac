#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampAlcohol(int x) {
    return max(0, min(200, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, l;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        l = 1;
        a.resize(n);
        for (int& x : a) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) x = rnd.next(0, 20);
            else if (bucket == 1) x = rnd.next(120, 145);
            else if (bucket == 2) x = rnd.next(180, 200);
            else x = rnd.next(0, 200);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        l = rnd.next(2, min(10, n));
        a.assign(n, 0);
        int target = rnd.next(124, 143);
        int base = target / l;
        int rem = target % l;
        for (int i = 0; i < n; ++i) {
            a[i] = clampAlcohol(base + (i % l < rem ? 1 : 0) + rnd.next(-1, 1));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 40);
        l = rnd.next(2, min(12, n));
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % l == 0) a[i] = rnd.next(120, 140);
            else a[i] = rnd.next(0, 8);
        }
    } else if (mode == 3) {
        n = rnd.next(10, 80);
        l = rnd.next(1, min(20, n));
        a.resize(n);
        int lo = rnd.next(0, 60);
        int hi = rnd.next(max(lo, 120), 200);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) a[i] = rnd.next(0, 200);
            else a[i] = rnd.next(lo, hi);
        }
    } else if (mode == 4) {
        n = rnd.next(1, 70);
        l = n;
        a.resize(n);
        int target = rnd.next(0, min(200 * n, 260));
        for (int i = 0; i < n; ++i) {
            int take = rnd.next(0, min(200, target));
            a[i] = take;
            target -= take;
        }
        shuffle(a.begin(), a.end());
    } else {
        n = rnd.next(120, 240);
        l = rnd.next(50, min(100, n));
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int wave = (i / max(1, l / 5)) % 4;
            if (wave == 0) a[i] = rnd.next(0, 5);
            else if (wave == 1) a[i] = rnd.next(1, 4);
            else if (wave == 2) a[i] = rnd.next(20, 45);
            else a[i] = rnd.next(80, 200);
        }
    }

    println(n, l);
    println(a);
    return 0;
}
