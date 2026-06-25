#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int valueFromMode(int mode) {
    if (mode == 0) return rnd.next(1, 10000);
    if (mode == 1) return rnd.next(-10000, -1);
    if (mode == 2) return rnd.next(-3, 3);
    if (rnd.next(4) == 0) return rnd.next(0, 1) ? -10000 : 10000;
    return rnd.next(-10000, 10000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 35);
    if (mode == 5) n = rnd.next(40, 90);

    int m = rnd.next(1, n);
    if (mode == 0) m = 1;
    if (mode == 1) m = min(n, rnd.next(2, 6));
    if (mode == 2) m = min(n, rnd.next(2, 8));

    vector<int> a(n);
    vector<int> v(n);

    if (mode == 0) {
        fill(a.begin(), a.end(), 1);
        for (int i = 0; i < n; ++i) v[i] = valueFromMode(rnd.next(3));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = i % m + 1;
            v[i] = valueFromMode(i % 3 == 0 ? 0 : 3);
        }
    } else if (mode == 2) {
        int pos = 0;
        while (pos < n) {
            int color = rnd.next(1, m);
            int len = rnd.next(1, min(6, n - pos));
            for (int j = 0; j < len; ++j) {
                a[pos + j] = color;
                v[pos + j] = valueFromMode(rnd.next(4));
            }
            pos += len;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, m);
            v[i] = valueFromMode(rnd.next(10) < 7 ? 1 : 3);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, m);
            v[i] = valueFromMode(2);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, m);
            v[i] = valueFromMode(3);
        }
    }

    println(n);
    println(m);
    for (int i = 0; i < n; ++i) println(a[i], v[i]);

    return 0;
}
