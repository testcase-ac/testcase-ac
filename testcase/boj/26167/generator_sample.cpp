#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(6, mode == 5 ? 20 : 12);
    int m = rnd.next(6, mode == 5 ? 20 : 12);
    vector<vector<int>> a(n, vector<int>(m, 1));

    if (mode == 0) {
        int lo = rnd.next(1, 30);
        int hi = rnd.next(lo, min(1000, lo + rnd.next(10, 200)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(lo, hi);
            }
        }
    } else if (mode == 1) {
        int base = rnd.next(1, 20);
        int rowStep = rnd.next(1, 30);
        int colStep = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = min(1000, base + i * rowStep + j * colStep + rnd.next(0, 5));
            }
        }
    } else if (mode == 2) {
        int low = rnd.next(1, 5);
        int high = rnd.next(50, 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = ((i + j + rnd.next(0, 1)) % 2 == 0) ? high : low;
            }
        }
    } else if (mode == 3) {
        int high = rnd.next(400, 1000);
        int bumps = rnd.next(6, min(30, n * m));
        for (int k = 0; k < bumps; ++k) {
            a[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = rnd.next(high / 2, high);
        }
    } else if (mode == 4) {
        int centers = rnd.next(2, 5);
        for (int c = 0; c < centers; ++c) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, m - 1);
            int value = rnd.next(100, 1000);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    int dist = abs(i - x) + abs(j - y);
                    a[i][j] = max(a[i][j], max(1, value - dist * rnd.next(20, 90)));
                }
            }
        }
    } else {
        int stripeWidth = rnd.next(1, 4);
        int high = rnd.next(100, 1000);
        int low = rnd.next(1, 20);
        bool vertical = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int band = (vertical ? j : i) / stripeWidth;
                a[i][j] = (band % 2 == 0) ? high - rnd.next(0, min(50, high - 1)) : low;
            }
        }
    }

    println(n, m);
    for (const auto& row : a) {
        println(row);
    }

    return 0;
}
