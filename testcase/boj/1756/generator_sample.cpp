#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_DIAMETER = 1000000000;

    int mode = rnd.next(0, 5);
    int d = rnd.next(1, 30);
    int n = rnd.next(1, 30);

    if (mode == 0) {
        d = rnd.next(1, 5);
        n = rnd.next(1, 7);
    } else if (mode == 3) {
        d = rnd.next(8, 40);
        n = rnd.next(1, d);
    } else if (mode == 4) {
        d = rnd.next(1, 12);
        n = rnd.next(d, 30);
    } else if (mode == 5) {
        d = rnd.next(1, 25);
        n = rnd.next(1, 25);
    }

    vector<int> oven(d), pizzas(n);

    if (mode == 0) {
        int lo = rnd.next(1, 6);
        int hi = rnd.next(lo, 12);
        for (int& x : oven) x = rnd.next(lo, hi);
        for (int& x : pizzas) x = rnd.next(lo, hi);
    } else if (mode == 1) {
        int bottleneck = rnd.next(1, 20);
        int wide = rnd.next(bottleneck, 80);
        for (int i = 0; i < d; ++i) {
            if (rnd.next(0, 4) == 0) {
                oven[i] = rnd.next(1, bottleneck);
            } else {
                oven[i] = rnd.next(bottleneck, wide);
            }
        }
        for (int& x : pizzas) x = rnd.next(1, wide);
    } else if (mode == 2) {
        int high = rnd.next(20, 100);
        for (int i = 0; i < d; ++i) {
            if (i % 2 == 0) {
                oven[i] = rnd.next(high / 2, high);
            } else {
                oven[i] = rnd.next(1, high / 2);
            }
        }
        for (int& x : pizzas) x = rnd.next(1, high);
    } else if (mode == 3) {
        int cur = rnd.next(20, 100);
        for (int i = 0; i < d; ++i) {
            cur = rnd.next(1, cur);
            oven[i] = cur + rnd.next(0, 15);
        }
        int minSeen = oven[0];
        for (int i = 1; i < d; ++i) minSeen = min(minSeen, oven[i]);
        for (int& x : pizzas) x = rnd.next(1, minSeen);
    } else if (mode == 4) {
        int diameter = rnd.next(1, 100);
        for (int& x : oven) x = diameter;
        for (int& x : pizzas) x = rnd.next(1, diameter);
    } else {
        int cap = rnd.next(1, 1000);
        for (int& x : oven) x = rnd.next(1, cap);
        for (int& x : pizzas) {
            if (rnd.next(0, 2) == 0) {
                x = rnd.next(cap + 1, min(MAX_DIAMETER, cap + 1000));
            } else {
                x = rnd.next(1, cap);
            }
        }
    }

    if (rnd.next(0, 9) == 0) {
        int pos = rnd.next(0, d - 1);
        oven[pos] = MAX_DIAMETER;
    }
    if (rnd.next(0, 9) == 0) {
        int pos = rnd.next(0, n - 1);
        pizzas[pos] = MAX_DIAMETER;
    }

    println(d, n);
    println(oven);
    println(pizzas);
    return 0;
}
