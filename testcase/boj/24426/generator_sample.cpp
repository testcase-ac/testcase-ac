#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 10);
    int mode = rnd.next(5);

    vector<vector<int>> a(n, vector<int>(n, 1));
    if (mode == 0) {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(5, 200)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(lo, hi);
            }
        }
    } else if (mode == 1) {
        int highRow = rnd.next(n);
        int highCol = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(1, 9);
                if (i == highRow || j == highCol) {
                    a[i][j] += rnd.next(100, 1000);
                }
            }
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = base + i * rnd.next(1, 8) + j * rnd.next(1, 8);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(1, 5);
            }
        }
        int spikes = rnd.next(n, 2 * n);
        for (int k = 0; k < spikes; ++k) {
            a[rnd.next(n)][rnd.next(n)] = rnd.next(1000, 100000);
        }
    } else {
        int start = rnd.next(1, 100000 - 2 * n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = start + (n - 1 - i) * rnd.next(1, 30) + (n - 1 - j) * rnd.next(1, 30);
            }
        }
    }

    int r = rnd.next(1, n);
    int c = rnd.next(1, n);
    while ((r == 1 && c == 1) || (r == n && c == n)) {
        r = rnd.next(1, n);
        c = rnd.next(1, n);
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }
    println(r, c);

    return 0;
}
