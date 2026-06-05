#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clipped(int value) {
    return max(0, min(100000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(0, 100000));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int value = rnd.next(0, 3);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        int peak = rnd.next(n - 2, n + 8);
        for (int i = 0; i < n; ++i) {
            a.push_back(clipped(peak - i + rnd.next(-1, 1)));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        int high = rnd.next(20, 80);
        int repeats = rnd.next(2, n);
        for (int i = 0; i < repeats; ++i) a.push_back(high);
        while ((int)a.size() < n) a.push_back(rnd.next(0, min(high, 8)));
    } else if (mode == 4) {
        n = rnd.next(8, 35);
        int lo = rnd.next(0, 20);
        int hi = rnd.next(lo, 120);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else if (mode == 5) {
        n = rnd.next(10, 60);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(0);
            } else {
                a.push_back(rnd.next(1, 100));
            }
        }
    } else if (mode == 6) {
        n = rnd.next(20, 80);
        int base = rnd.next(99900, 100000);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(base, 100000));
    } else {
        n = rnd.next(80, 180);
        for (int i = 0; i < n; ++i) {
            int band = rnd.next(0, 4);
            if (band == 0) {
                a.push_back(rnd.next(0, 5));
            } else if (band == 1) {
                a.push_back(rnd.next(6, 60));
            } else if (band == 2) {
                a.push_back(rnd.next(61, 1000));
            } else {
                a.push_back(rnd.next(90000, 100000));
            }
        }
    }

    if (mode != 2) shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
