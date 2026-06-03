#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int m;
    int k = rnd.next(1, 5);

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
    } else if (mode == 3) {
        n = rnd.next(6, 12);
        m = rnd.next(6, 12);
    } else if (mode == 4) {
        n = rnd.next(2, 4);
        m = rnd.next(8, 15);
    } else if (mode == 5) {
        n = rnd.next(8, 15);
        m = rnd.next(2, 4);
    } else if (mode == 6) {
        n = rnd.next(1, 1000);
        m = rnd.next(1, 3);
    } else {
        n = rnd.next(1, 3);
        m = rnd.next(1, 1000);
    }

    vector<vector<int>> a(n, vector<int>(m));

    if (mode <= 1) {
        int lo = rnd.next(0, 30);
        int hi = rnd.next(lo, 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(lo, hi);
            }
        }
    } else if (mode <= 3) {
        int high = rnd.next(700, 1000);
        int low = rnd.next(0, 80);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j + rnd.next(0, 1)) % 2 == 0) {
                    a[i][j] = rnd.next(max(0, high - 120), high);
                } else {
                    a[i][j] = rnd.next(low);
                }
            }
        }
    } else if (mode <= 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(0, 200);
            }
        }
        int centers = rnd.next(1, min(5, n * m));
        for (int c = 0; c < centers; ++c) {
            int r = rnd.next(n);
            int col = rnd.next(m);
            a[r][col] = rnd.next(800, 1000);
            if (r + 1 < n) {
                a[r + 1][col] = rnd.next(700, 1000);
            }
            if (col + 1 < m) {
                a[r][col + 1] = rnd.next(700, 1000);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int base = (i + j) % 3 == 0 ? rnd.next(600, 1000) : rnd.next(0, 250);
                a[i][j] = base;
            }
        }
    }

    println(n, m, k);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
