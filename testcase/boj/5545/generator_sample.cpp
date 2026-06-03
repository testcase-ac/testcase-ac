#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampValue(int x, int lo, int hi) {
    return max(lo, min(hi, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int a;
    int b;
    int c;
    vector<int> d;

    if (mode == 0) {
        n = rnd.next(1, 5);
        a = rnd.next(1, 20);
        b = rnd.next(1, 20);
        c = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) d.push_back(rnd.next(1, 200));
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        a = rnd.next(1, 30);
        b = rnd.next(1, 8);
        c = rnd.next(1, 400);
        for (int i = 0; i < n; ++i) d.push_back(rnd.next(300, 10000));
    } else if (mode == 2) {
        n = rnd.next(4, 15);
        a = rnd.next(20, 200);
        b = rnd.next(5, 80);
        c = rnd.next(100, 3000);
        int base = max(1, c * b / a);
        for (int i = 0; i < n; ++i) {
            int spread = rnd.next(-40, 40);
            d.push_back(clampValue(base + spread, 1, 10000));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        a = rnd.next(300, 1000);
        b = rnd.next(300, 1000);
        c = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) d.push_back(rnd.next(1, 10000));
        if (rnd.next(0, 1) == 0) {
            sort(d.begin(), d.end());
        } else {
            sort(d.begin(), d.end(), greater<int>());
        }
    } else if (mode == 4) {
        n = rnd.next(8, 25);
        a = rnd.next(1, 1000);
        b = rnd.next(1, 1000);
        c = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                d.push_back(rnd.any(vector<int>{1, 2, 9999, 10000}));
            } else {
                d.push_back(rnd.next(1, 10000));
            }
        }
    } else {
        n = rnd.next(1, 100);
        a = rnd.next(1, 1000);
        b = rnd.next(1, 1000);
        c = rnd.next(1, 10000);
        int lo = rnd.next(1, 9000);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i < n; ++i) d.push_back(rnd.next(lo, hi));
    }

    println(n);
    println(a, b);
    println(c);
    for (int x : d) println(x);

    return 0;
}
