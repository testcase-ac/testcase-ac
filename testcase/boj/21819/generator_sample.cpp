#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 25);
    int k = rnd.next(0, 30);
    int l = rnd.next(0, 30);

    vector<int> c(n);

    if (mode == 0) {
        k = 0;
        l = rnd.next(0, 30);
        for (int& x : c) x = rnd.next(0, n + 5);
    } else if (mode == 1) {
        k = rnd.next(0, 30);
        l = 0;
        for (int& x : c) x = rnd.next(0, n + 5);
    } else if (mode == 2) {
        int h = rnd.next(1, n);
        k = rnd.next(1, 8);
        l = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            if (i < h) {
                c[i] = rnd.next(max(0, h - k - 1), h + 2);
            } else {
                c[i] = rnd.next(0, h);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(0, min(n, 12));
        k = rnd.next(1, 12);
        l = rnd.next(1, n);
        for (int i = 0; i < n; ++i) c[i] = max(0, base + rnd.next(-2, 2));
    } else if (mode == 4) {
        k = rnd.next(1, 20);
        l = rnd.next(n, 30);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(0, n);
    } else if (mode == 5) {
        n = rnd.next(1, 8);
        k = rnd.next(0, 100000);
        l = rnd.next(0, 100000);
        c.assign(n, 0);
        for (int& x : c) x = rnd.next(0, 100000);
    } else if (mode == 6) {
        k = rnd.next(1, 12);
        l = rnd.next(1, n);
        for (int i = 0; i < n; ++i) c[i] = i % 2 == 0 ? rnd.next(0, 3) : rnd.next(n, 100);
    } else {
        int ceiling = rnd.next(0, n + 10);
        for (int& x : c) x = rnd.next(0, ceiling);
    }

    shuffle(c.begin(), c.end());

    println(n, k, l);
    println(c);

    return 0;
}
