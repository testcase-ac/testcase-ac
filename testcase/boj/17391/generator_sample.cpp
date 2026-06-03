#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    }

    int limit = max(n, m);
    vector<vector<int>> a(n, vector<int>(m, 1));

    if (mode == 0 || mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(1, limit);
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = 1;
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(max(1, limit / 2), limit);
            }
        }
    } else if (mode == 4) {
        int smallCap = rnd.next(1, min(limit, 3));
        int largeThreshold = max(1, limit - rnd.next(0, min(limit - 1, 3)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j + rnd.next(2)) % 3 == 0) {
                    a[i][j] = rnd.next(largeThreshold, limit);
                } else {
                    a[i][j] = rnd.next(1, smallCap);
                }
            }
        }
    } else {
        int cap = rnd.next(1, limit);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(1, cap);
            }
        }
        for (int i = 0; i < n; ++i) {
            a[i][m - 1] = rnd.next(1, limit);
        }
        for (int j = 0; j < m; ++j) {
            a[n - 1][j] = rnd.next(1, limit);
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
