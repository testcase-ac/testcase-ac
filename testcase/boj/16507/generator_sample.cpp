#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r, c;
    if (mode == 0) {
        r = 1;
        c = rnd.next(1, 20);
    } else if (mode == 1) {
        r = rnd.next(1, 20);
        c = 1;
    } else if (mode == 2) {
        r = rnd.next(2, 8);
        c = rnd.next(2, 8);
    } else if (mode == 3) {
        r = rnd.next(3, 12);
        c = rnd.next(3, 12);
    } else if (mode == 4) {
        r = rnd.next(2, 5);
        c = rnd.next(10, 25);
    } else {
        r = rnd.next(10, 25);
        c = rnd.next(2, 5);
    }

    int q = rnd.next(1, min(30, r * c + 10));
    vector<vector<int>> a(r, vector<int>(c));
    int valueMode = rnd.next(0, 4);
    int base = rnd.next(1, 1000);
    int stepR = rnd.next(1, 17);
    int stepC = rnd.next(1, 19);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (valueMode == 0) {
                a[i][j] = base;
            } else if (valueMode == 1) {
                a[i][j] = 1 + (i * stepR + j * stepC + base) % 1000;
            } else if (valueMode == 2) {
                a[i][j] = ((i + j) % 2 == 0) ? 1 : 1000;
            } else if (valueMode == 3) {
                a[i][j] = rnd.next(1, 20);
            } else {
                a[i][j] = rnd.next(1, 1000);
            }
        }
    }

    println(r, c, q);
    for (int i = 0; i < r; ++i) {
        println(a[i]);
    }

    for (int i = 0; i < q; ++i) {
        int queryMode = rnd.next(0, 5);
        int r1, c1, r2, c2;
        if (queryMode == 0) {
            r1 = rnd.next(1, r);
            c1 = rnd.next(1, c);
            r2 = r1;
            c2 = c1;
        } else if (queryMode == 1) {
            r1 = rnd.next(1, r);
            r2 = r1;
            c1 = rnd.next(1, c);
            c2 = rnd.next(c1, c);
        } else if (queryMode == 2) {
            c1 = rnd.next(1, c);
            c2 = c1;
            r1 = rnd.next(1, r);
            r2 = rnd.next(r1, r);
        } else if (queryMode == 3) {
            r1 = 1;
            c1 = 1;
            r2 = r;
            c2 = c;
        } else {
            r1 = rnd.next(1, r);
            r2 = rnd.next(r1, r);
            c1 = rnd.next(1, c);
            c2 = rnd.next(c1, c);
        }
        println(r1, c1, r2, c2);
    }

    return 0;
}
