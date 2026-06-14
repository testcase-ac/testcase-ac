#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(8, 16);
    } else if (mode == 2) {
        n = rnd.next(10, 25);
    } else if (mode == 3) {
        n = rnd.next(20, 45);
    } else if (mode == 4) {
        n = rnd.next(6, 18);
    } else if (mode == 5) {
        n = rnd.next(30, 70);
    } else {
        n = rnd.next(80, 100);
    }

    int maxM = min(10, n);
    int m;
    if (mode == 0) {
        m = rnd.next(1, maxM);
    } else if (mode == 1) {
        m = 1;
    } else if (mode == 2) {
        m = maxM;
    } else if (mode == 3) {
        m = rnd.next(max(1, maxM - 3), maxM);
    } else {
        m = rnd.next(1, maxM);
    }

    vector<int> p(n);
    if (mode == 0) {
        for (int& x : p) x = rnd.next(1, 20);
    } else if (mode == 1) {
        int lo = rnd.next(1, 5);
        int hi = rnd.next(16, 20);
        for (int i = 0; i < n; ++i) p[i] = (i % 2 == 0 ? lo : hi);
    } else if (mode == 2) {
        int start = rnd.next(1, 5);
        int step = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) p[i] = min(20, start + i * step);
    } else if (mode == 3) {
        int value = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 5) == 0) value = rnd.next(1, 20);
            p[i] = value;
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) p[i] = rnd.next(1, 4);
        int spikes = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < spikes; ++i) p[rnd.next(0, n - 1)] = rnd.next(15, 20);
    } else if (mode == 5) {
        int hi = rnd.next(10, 20);
        for (int i = 0; i < n; ++i) p[i] = rnd.next(1, hi);
    } else {
        for (int i = 0; i < n; ++i) p[i] = rnd.next(1, 20);
    }

    println(n, m);
    println(p);
    return 0;
}
