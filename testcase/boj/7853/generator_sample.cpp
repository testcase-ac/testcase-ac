#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);
    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 2);
    } else if (mode == 1) {
        n = rnd.next(1, 3);
        m = rnd.next(5, 10);
    } else if (mode == 2) {
        n = rnd.next(5, 10);
        m = rnd.next(1, 3);
    }

    int low = rnd.next(1, 4);
    int high = rnd.next(low, min(40, low + rnd.next(0, 12)));
    vector<vector<int>> a(n, vector<int>(m, low));

    if (mode == 0) {
        high = rnd.next(20, 40);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next() < 0.45 ? high : rnd.next(1, 3);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = min(40, base + i + j + rnd.next(0, 2));
            }
        }
    } else if (mode == 4) {
        int centerI = rnd.next(0, n - 1);
        int centerJ = rnd.next(0, m - 1);
        int peak = rnd.next(8, 25);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int dist = abs(i - centerI) + abs(j - centerJ);
                a[i][j] = max(1, peak - 2 * dist + rnd.next(-1, 1));
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool onStripe = (i + j + rnd.next(0, 1)) % 3 == 0;
                a[i][j] = onStripe ? rnd.next(10, 30) : rnd.next(1, 5);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(low, high);
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
