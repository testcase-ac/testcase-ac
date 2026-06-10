#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int l = 1;
    vector<int> a;

    if (mode == 0) {
        l = rnd.next(1, 18);
        a.assign(l, 0);
        for (int i = 0; i < l; ++i) {
            a[i] = rnd.next(-20, 0);
        }
    } else if (mode == 1) {
        l = rnd.next(2, 35);
        a.assign(l, rnd.next(-8, 3));
        int spikes = rnd.next(1, min(5, l));
        for (int i = 0; i < spikes; ++i) {
            int pos = rnd.next(0, l - 1);
            a[pos] = rnd.next(10, 80);
        }
    } else if (mode == 2) {
        l = rnd.next(8, 60);
        a.assign(l, rnd.next(-12, 2));
        int d = rnd.next(1, min(12, l));
        int bonus = rnd.next(4, 25);
        for (int pos = d; pos <= l; pos += d) {
            a[pos - 1] += bonus + rnd.next(0, 8);
        }
    } else if (mode == 3) {
        l = rnd.next(6, 42);
        a.assign(l, 0);
        int d1 = rnd.next(1, min(8, l));
        int d2 = rnd.next(1, min(8, l));
        int value = rnd.next(3, 18);
        for (int pos = d1; pos <= l; pos += d1) {
            a[pos - 1] += value;
        }
        for (int pos = d2; pos <= l; pos += d2) {
            a[pos - 1] += value;
        }
        for (int i = 0; i < l; ++i) {
            a[i] += rnd.next(-2, 2);
        }
    } else if (mode == 4) {
        l = rnd.next(1, 30);
        a.assign(l, 0);
        for (int i = 0; i < l; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) {
                a[i] = -50000;
            } else if (pick == 1) {
                a[i] = 50000;
            } else {
                a[i] = rnd.next(-50, 50);
            }
        }
    } else if (mode == 5) {
        l = rnd.next(40, 120);
        a.assign(l, 0);
        int lo = rnd.next(-100, 0);
        int hi = rnd.next(0, 100);
        for (int i = 0; i < l; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    } else {
        l = rnd.next(2, 50);
        a.assign(l, rnd.next(-5, 0));
        int period = rnd.next(2, min(10, l));
        for (int i = period - 1; i < l; i += period) {
            a[i] = rnd.next(1, 40);
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    }

    println(l);
    println(a);

    return 0;
}
