#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int l;
    int a;
    int b;
    vector<int> d;
    vector<int> h;

    if (mode == 0) {
        n = rnd.next(1, 3);
        l = rnd.next(1, 4);
        a = rnd.next(1, min(10, l));
        b = rnd.next(1, 8);
    } else if (mode == 1) {
        l = rnd.next(8, 30);
        n = rnd.next(4, 12);
        a = rnd.next(1, 10);
        b = rnd.next(1, 12);
    } else if (mode == 2) {
        l = rnd.next(10, 40);
        n = rnd.next(5, 16);
        a = rnd.next(1, 10);
        b = rnd.next(1, 20);
    } else if (mode == 3) {
        l = rnd.next(15, 60);
        n = rnd.next(6, 20);
        a = rnd.next(1, 10);
        b = rnd.next(5, 50);
    } else if (mode == 4) {
        l = rnd.next(2, 100000);
        n = rnd.next(2, 10);
        a = rnd.next(1, 10);
        b = rnd.next(1, 100000);
    } else {
        l = 100000;
        n = rnd.next(3, 15);
        a = rnd.next(1, 10);
        b = rnd.next(1, 100000);
    }

    d.resize(n);
    h.resize(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(1, l);
            h[i] = rnd.next(1, 10);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, l);
        int radius = rnd.next(0, min(5, l - 1));
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(max(1, center - radius), min(l, center + radius));
            h[i] = rnd.next(1, b * rnd.next(1, 6));
        }
    } else if (mode == 2) {
        int repeated = rnd.next(1, l);
        for (int i = 0; i < n; ++i) {
            d[i] = (rnd.next(0, 99) < 60) ? repeated : rnd.next(1, l);
            h[i] = rnd.next(1, 100);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int base = 1 + (long long)i * (l - 1) / max(1, n - 1);
            d[i] = min(l, max(1, base + rnd.next(-2, 2)));
            h[i] = rnd.next(1, 200);
        }
        shuffle(d.begin(), d.end());
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.any(vector<int>{1, l, rnd.next(1, l)});
            h[i] = rnd.next(1, 100000);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            d[i] = rnd.next(max(1, l - 30), l);
            h[i] = rnd.next(max(1, b - 5), 100000);
        }
    }

    println(n, l);
    println(a, b);
    println(d);
    println(h);

    return 0;
}
