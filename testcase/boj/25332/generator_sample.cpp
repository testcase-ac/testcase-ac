#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_VALUE = 1;
const int MAX_VALUE = 10000;

vector<int> randomArray(int n, int lo, int hi) {
    vector<int> a(n);
    for (int& x : a) x = rnd.next(lo, hi);
    return a;
}

void printCase(const vector<int>& a, const vector<int>& b) {
    println((int)a.size());
    println(a);
    println(b);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> a, b;

    if (mode == 0) {
        n = rnd.next(1, 30);
        int lo = rnd.next(1, 50);
        int hi = rnd.next(lo, min(MAX_VALUE, lo + rnd.next(0, 200)));
        a = randomArray(n, lo, hi);
        b = a;
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        int small = rnd.next(1, 20);
        int large = rnd.next(9000, MAX_VALUE);
        a.assign(n, small);
        b.assign(n, large);
        if (rnd.next(0, 1)) swap(a, b);
    } else if (mode == 2) {
        n = rnd.next(2, 60);
        a.resize(n);
        b.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                int x = rnd.next(1, MAX_VALUE);
                a[i] = x;
                b[i] = x;
            } else if (rnd.next(0, 1)) {
                a[i] = rnd.next(1, 5000);
                b[i] = a[i] + rnd.next(1, 5000);
            } else {
                b[i] = rnd.next(1, 5000);
                a[i] = b[i] + rnd.next(1, 5000);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(3, 70);
        a.resize(n);
        b.resize(n);
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(20, 300);
            int delta = rnd.next(-10, 10);
            a[i] = base;
            b[i] = base + delta;
            if (b[i] < MIN_VALUE) b[i] = MIN_VALUE;
            if (b[i] > MAX_VALUE) b[i] = MAX_VALUE;
        }
    } else if (mode == 4) {
        n = rnd.next(1, 80);
        a.resize(n);
        b.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a[i] = MIN_VALUE;
                b[i] = MAX_VALUE;
            } else if (rnd.next(0, 2) == 0) {
                a[i] = MAX_VALUE;
                b[i] = MIN_VALUE;
            } else {
                a[i] = rnd.next(1, MAX_VALUE);
                b[i] = rnd.next(1, MAX_VALUE);
            }
        }
    } else {
        n = rnd.next(20, 120);
        a.resize(n);
        b.resize(n);
        int lo = rnd.next(1, 100);
        int hi = rnd.next(lo, min(MAX_VALUE, lo + 50));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
            b[i] = rnd.next(lo, hi);
        }
        int copies = rnd.next(1, n / 4);
        for (int it = 0; it < copies; ++it) {
            int pos = rnd.next(0, n - 1);
            b[pos] = a[pos];
        }
    }

    printCase(a, b);
    return 0;
}
