#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    int c;
    vector<int> w(n);

    if (mode == 0) {
        c = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(0, min(c, 2));
        }
    } else if (mode == 1) {
        c = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            w[i] = (i % 2 == 0 ? 0 : rnd.next(max(1, c - 2), c));
        }
    } else if (mode == 2) {
        c = rnd.next(2, 50);
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(0, c);
        }
        int pos = rnd.next(0, n - 1);
        w[pos] = c;
    } else if (mode == 3) {
        c = rnd.next(10, 100);
        int base = rnd.next(0, min(c, 5));
        for (int i = 0; i < n; ++i) {
            w[i] = min(c, base + i % 7);
        }
    } else if (mode == 4) {
        c = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            w[i] = rnd.next(0, c);
        }
    } else {
        n = rnd.next(20, 60);
        c = rnd.next(3, 40);
        w.assign(n, 0);
        int block = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            if (i % block == 0) {
                w[i] = rnd.next(max(1, c / 2), c);
            } else {
                w[i] = rnd.next(0, min(c, 3));
            }
        }
    }

    println(n, c);
    println(w);
    return 0;
}
