#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n = sizeMode == 0 ? 3 : rnd.next(3, 12);
    int q = rnd.next(1, 30);
    if (rnd.next(6) == 0) {
        q = rnd.next(31, 80);
    }

    int valueMode = rnd.next(5);
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = 0;
            if (valueMode == 0) {
                value = rnd.next(0, 20);
            } else if (valueMode == 1) {
                value = rnd.next(5) == 0 ? 10000 : rnd.next(0, 9);
            } else if (valueMode == 2) {
                value = (i + 1) * rnd.next(0, 7) + (j + 1) * rnd.next(0, 5);
            } else if (valueMode == 3) {
                value = rnd.next(3) == 0 ? 0 : rnd.next(9000, 10000);
            } else {
                value = (i == j || j == n - 1 - i) ? rnd.next(0, 10000) : rnd.next(0, 30);
            }
            a[i][j] = value;
        }
    }

    println(n, q);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    for (int query = 0; query < q; ++query) {
        int sx = rnd.next(1, n);
        int sy = rnd.next(1, n);
        int l = rnd.next(0, sx - 1);

        int queryMode = rnd.next(6);
        if (queryMode == 0) {
            sx = 1;
            l = 0;
        } else if (queryMode == 1) {
            sx = n;
            l = n - 1;
        } else if (queryMode == 2) {
            l = 0;
        } else if (queryMode == 3) {
            l = sx - 1;
        } else if (queryMode == 4) {
            sy = 1;
        } else {
            sy = n;
        }

        println(sx, sy, l);
    }

    return 0;
}
