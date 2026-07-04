#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
    } else {
        n = rnd.next(3, 8);
    }

    int q = rnd.next(1, 12);
    println(n, q);

    int lo = rnd.next(0, 50);
    int hi = rnd.next(lo, 100);
    for (int i = 1; i <= n; ++i) {
        vector<int> row;
        for (int j = 1; j <= n; ++j) {
            if (mode == 2) {
                row.push_back((i + j + rnd.next(0, 3)) % 2 == 0 ? lo : hi);
            } else {
                row.push_back(rnd.next(lo, hi));
            }
        }
        println(row);
    }

    for (int i = 1; i <= q; ++i) {
        int r1 = 1;
        int c1 = 1;
        int r2 = n;
        int c2 = n;

        int shape = rnd.next(0, 5);
        if (mode == 0 || shape == 0) {
            r1 = r2 = rnd.next(1, n);
            c1 = c2 = rnd.next(1, n);
        } else if (shape == 1) {
            r1 = r2 = rnd.next(1, n);
            c1 = rnd.next(1, n);
            c2 = rnd.next(c1, n);
        } else if (shape == 2) {
            r1 = rnd.next(1, n);
            r2 = rnd.next(r1, n);
            c1 = c2 = rnd.next(1, n);
        } else if (shape == 3) {
            r1 = c1 = 1;
            r2 = c2 = n;
        } else {
            r1 = rnd.next(1, n);
            c1 = rnd.next(1, n);
            r2 = rnd.next(r1, n);
            c2 = rnd.next(c1, n);
        }

        int v;
        if (i == 1 && rnd.next(0, 1) == 0) {
            v = 0;
        } else if (i == q && rnd.next(0, 1) == 0) {
            v = 100;
        } else {
            v = rnd.next(0, 100);
        }

        println(r1, c1, r2, c2, v);
    }

    return 0;
}
