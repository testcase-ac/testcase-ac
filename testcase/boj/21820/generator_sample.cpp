#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int l;
    vector<int> c;

    if (mode == 0) {
        n = rnd.next(1, 8);
        l = rnd.next(0, min(100000, n));
        c.resize(n);
        for (int& x : c) x = rnd.next(0, n + 2);
    } else if (mode == 1) {
        n = rnd.next(3, 20);
        int h = rnd.next(1, n);
        l = rnd.next(0, n);
        c.reserve(n);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(-2, 2);
            c.push_back(max(0, h + delta));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 30);
        int h = rnd.next(1, n);
        l = rnd.next(0, h);
        c.assign(n, 0);
        for (int i = 0; i < h; ++i) c[i] = rnd.next(max(0, h - 1), h);
        for (int i = h; i < n; ++i) c[i] = rnd.next(0, h + 1);
    } else if (mode == 3) {
        n = rnd.next(8, 40);
        l = rnd.next(0, 100000);
        c.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(4) == 0) {
                c[i] = 100000;
            } else {
                c[i] = rnd.next(0, min(100000, n + 5));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        l = rnd.next(0, 100000);
        c.resize(n);
        int high = rnd.next(0, 100000);
        int low = rnd.next(0, min(high, 20));
        for (int i = 0; i < n; ++i) c[i] = rnd.next(low, high);
    } else {
        n = rnd.next(90, 150);
        int h = rnd.next(20, min(100, n));
        l = rnd.next(max(0, h - 5), min(100000, h + 5));
        c.resize(n);
        for (int i = 0; i < n; ++i) {
            if (i < h) {
                c[i] = rnd.next(max(0, h - 1), h + 1);
            } else {
                c[i] = rnd.next(0, h);
            }
        }
    }

    shuffle(c.begin(), c.end());

    println(n, l);
    println(c);

    return 0;
}
