#include "testlib.h"
#include <vector>

using namespace std;

static void printCase(const vector<int>& a) {
    println((int)a.size());
    println(a);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        int n = rnd.next(1, 35);
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(1, 20);
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 45);
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(1, 99);
        }
        int pos = rnd.next(0, n - 2);
        int x = rnd.next(1, 49);
        a[pos] = x;
        a[pos + 1] = 100 - x;
    } else if (mode == 2) {
        int n = rnd.next(4, 60);
        a.resize(n);
        int pattern = rnd.next(0, 2);
        if (pattern == 0) {
            for (int i = 0; i < n; ++i) {
                a[i] = (i < 4 ? 25 : rnd.next(1, 24));
            }
        } else if (pattern == 1) {
            for (int i = 0; i < n; ++i) {
                a[i] = (i < 3 ? (i == 2 ? 34 : 33) : rnd.next(1, 32));
            }
        } else {
            int ones = rnd.next(1, min(98, n - 1));
            for (int i = 0; i < n; ++i) {
                a[i] = (i < ones ? 1 : rnd.next(2, 98));
            }
            a[ones] = 100 - ones;
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 3) {
        int n = rnd.next(2, 50);
        a.resize(n);
        for (int& x : a) {
            x = rnd.next(1, 99);
        }
        int first = rnd.next(0, n - 2);
        int second = rnd.next(first + 1, n - 1);
        a[first] = 50;
        a[second] = 50;
    } else if (mode == 4) {
        int n = rnd.next(40, 120);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i % 5 == 0) {
                a[i] = rnd.next(45, 55);
            } else if (i % 5 == 1) {
                a[i] = rnd.next(1, 10);
            } else {
                a[i] = rnd.next(20, 80);
            }
        }
    } else if (mode == 5) {
        int n = rnd.next(70, 180);
        a.resize(n);
        int base = rnd.next(1, 49);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? base : 100 - base);
        }
        for (int i = 0; i < n / 5; ++i) {
            a[rnd.next(0, n - 1)] = rnd.next(1, 99);
        }
    } else {
        int n = rnd.next(1, 100);
        a.resize(n);
        int lo = rnd.next(1, 90);
        int hi = rnd.next(lo, 99);
        for (int& x : a) {
            x = rnd.next(lo, hi);
        }
    }

    printCase(a);
    return 0;
}
