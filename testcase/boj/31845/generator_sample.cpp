#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(-3, 3);
        }
    } else if (mode == 1) {
        n = rnd.next(5, 12);
        m = rnd.next(1, 1000);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a[i] = rnd.next(1, 1000);
            } else if (i % 3 == 1) {
                a[i] = rnd.next(-1000, -1);
            } else {
                a[i] = 0;
            }
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(6, 20);
        m = rnd.next(1, n);
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(1, 30);
        }
    } else if (mode == 3) {
        n = rnd.next(6, 20);
        m = rnd.next(1, n);
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(-30, 0);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 30);
        int positiveCount = rnd.next(1, n);
        m = rnd.next(max(1, positiveCount / 2), min(1000, positiveCount + 5));
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i < positiveCount) {
                a[i] = rnd.next(1, 200);
            } else {
                a[i] = rnd.next(-200, 0);
            }
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 5) {
        n = rnd.next(2, 18);
        m = rnd.next(1, 1000);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) {
                a[i] = -1000;
            } else if (pick == 1) {
                a[i] = 1000;
            } else if (pick == 2) {
                a[i] = 0;
            } else {
                a[i] = rnd.next(-10, 10);
            }
        }
    } else {
        n = rnd.next(40, 80);
        m = rnd.next(1, 1000);
        a.resize(n);
        int lo = rnd.next(-1000, 0);
        int hi = rnd.next(0, 1000);
        for (int& x : a) {
            x = rnd.next(lo, hi);
        }
    }

    println(n, m);
    println(a);

    return 0;
}
