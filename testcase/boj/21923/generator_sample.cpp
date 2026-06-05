#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int boundedValue(int lo, int hi) {
    return rnd.next(max(lo, -10000), min(hi, 10000));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 2);
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1, 18);
    } else if (mode == 2) {
        n = rnd.next(1, 18);
        m = 1;
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    }

    vector<vector<int>> a(n, vector<int>(m, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = boundedValue(-5, 5);
            }
        }
    } else if (mode == 1 || mode == 2) {
        int lo = rnd.any(vector<int>{-10000, -20, -3, 0});
        int hi = rnd.any(vector<int>{0, 3, 20, 10000});
        if (lo > hi) {
            swap(lo, hi);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = boundedValue(lo, hi);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(-30, 30);
        int rowStep = rnd.next(-8, 8);
        int colStep = rnd.next(-8, 8);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = boundedValue(base + rowStep * i + colStep * j - 3,
                                      base + rowStep * i + colStep * j + 3);
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(-2, 2);
            }
        }
        int special = rnd.next(1, max(1, n * m / 4));
        for (int k = 0; k < special; ++k) {
            int i = rnd.next(n);
            int j = rnd.next(m);
            a[i][j] = rnd.any(vector<int>{-10000, -1000, 1000, 10000});
        }
    } else {
        int good = rnd.next(15, 80);
        int bad = rnd.next(-80, -15);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = bad + rnd.next(-5, 5);
            }
        }

        int turnRow = rnd.next(n);
        for (int i = n - 1; i >= turnRow; --i) {
            a[i][0] = good + rnd.next(-5, 5);
        }
        for (int j = 0; j < m; ++j) {
            a[turnRow][j] = good + rnd.next(-5, 5);
        }
        for (int i = turnRow; i < n; ++i) {
            a[i][m - 1] = good + rnd.next(-5, 5);
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
