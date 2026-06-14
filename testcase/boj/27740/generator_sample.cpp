#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(3, 80);
    vector<int> a(n, 0);

    if (mode == 0) {
        a[rnd.next(n)] = 1;
    } else if (mode == 1) {
        int l = rnd.next(n);
        int r = rnd.next(l, n - 1);
        for (int i = l; i <= r; ++i) {
            a[i] = 1;
        }
    } else if (mode == 2) {
        int parity = rnd.next(2);
        for (int i = parity; i < n; i += 2) {
            a[i] = 1;
        }
    } else if (mode == 3) {
        a[0] = 1;
        a[n - 1] = 1;
        int extra = rnd.next(0, min(n - 2, 8));
        for (int i = 0; i < extra; ++i) {
            a[rnd.next(1, n - 2)] = 1;
        }
    } else if (mode == 4) {
        double density = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next() < density;
        }
    } else {
        int blocks = rnd.next(2, 5);
        for (int b = 0; b < blocks; ++b) {
            int l = rnd.next(n);
            int len = rnd.next(1, min(8, n - l));
            for (int i = l; i < l + len; ++i) {
                a[i] = 1;
            }
        }
    }

    if (find(a.begin(), a.end(), 1) == a.end()) {
        a[rnd.next(n)] = 1;
    }

    println(n);
    println(a);

    return 0;
}
