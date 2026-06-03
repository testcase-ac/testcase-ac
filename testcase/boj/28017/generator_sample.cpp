#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;

    if (mode == 0) {
        n = 2;
        m = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        m = 2;
    } else if (mode == 2) {
        n = rnd.next(3, 9);
        m = rnd.next(3, 9);
    } else if (mode == 3) {
        n = rnd.next(8, 18);
        m = rnd.next(3, 10);
    } else if (mode == 4) {
        n = rnd.next(4, 12);
        m = rnd.next(8, 18);
    } else {
        n = rnd.next(2, 20);
        m = rnd.next(2, 20);
    }

    vector<vector<int>> a(n, vector<int>(m));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(1, 30);
            }
        }
    } else if (mode == 1) {
        int low = rnd.next(1, 20);
        int high = rnd.next(50, 200);
        for (int i = 0; i < n; ++i) {
            a[i][0] = (i % 2 == 0 ? low : high) + rnd.next(0, 5);
            a[i][1] = (i % 2 == 0 ? high : low) + rnd.next(0, 5);
        }
    } else if (mode == 2) {
        int cheap = rnd.next(1, 8);
        int expensive = rnd.next(80, 300);
        for (int i = 0; i < n; ++i) {
            int best = rnd.next(m);
            for (int j = 0; j < m; ++j) {
                a[i][j] = expensive + rnd.next(0, 40);
            }
            a[i][best] = cheap + rnd.next(0, 5);
        }
    } else if (mode == 3) {
        int first = rnd.next(m);
        int second = rnd.next(m - 1);
        if (second >= first) ++second;

        for (int i = 0; i < n; ++i) {
            int preferred = (i % 3 == 0 ? first : second);
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(30, 120);
            }
            a[i][preferred] = rnd.next(1, 12);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(1, 40);
            for (int j = 0; j < m; ++j) {
                a[i][j] = min(10000, base + abs(j - (i % m)) * rnd.next(1, 8) + rnd.next(0, 6));
            }
        }
    } else {
        int lo = rnd.next(1, 9000);
        int hi = rnd.next(lo, 10000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(lo, hi);
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
