#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedValue(int lo, int hi) {
    return rnd.next(max(lo, -127), min(hi, 127));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode == 4) {
        n = rnd.next(5, 14);
    } else {
        n = rnd.next(3, 10);
    }

    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = boundedValue(-127, -1);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = boundedValue(0, 30);
    } else if (mode == 2) {
        int lo = rnd.next(-40, -5);
        int hi = rnd.next(5, 40);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = boundedValue(lo, hi);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = boundedValue(-35, 8);

        int r1 = rnd.next(n);
        int r2 = rnd.next(r1, n - 1);
        int c1 = rnd.next(n);
        int c2 = rnd.next(c1, n - 1);
        for (int i = r1; i <= r2; ++i)
            for (int j = c1; j <= c2; ++j)
                a[i][j] = boundedValue(10, 55);
    } else {
        int positiveRow = rnd.next(n);
        int positiveCol = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == positiveRow || j == positiveCol) {
                    a[i][j] = boundedValue(1, 45);
                } else {
                    a[i][j] = boundedValue(-50, 10);
                }
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
