#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(2, 9);
        m = rnd.next(1, 3);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(4, 12);
    } else {
        n = rnd.next(3, 12);
        m = rnd.next(3, 12);
    }

    vector<vector<int>> glass(n, vector<int>(m, 0));

    if (mode <= 2) {
        int threshold = rnd.next(20, 85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                glass[i][j] = rnd.next(1, 100) <= threshold;
            }
        }
    } else if (mode == 3) {
        int start = rnd.next(0, m - 1);
        glass[n - 1][start] = 1;
        for (int i = n - 2; i >= 0; --i) {
            int lo = max(0, start - 1);
            int hi = min(m - 1, start + 1);
            start = rnd.next(lo, hi);
            glass[i][start] = 1;

            int extra = rnd.next(0, min(2, m - 1));
            for (int k = 0; k < extra; ++k) {
                glass[i][rnd.next(0, m - 1)] = 1;
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            int stripe = rnd.next(0, 1);
            for (int j = 0; j < m; ++j) {
                glass[i][j] = ((i + j + stripe) % 2 == 0);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int ones = rnd.next(0, m);
            vector<int> cols(m);
            for (int j = 0; j < m; ++j) {
                cols[j] = j;
            }
            shuffle(cols.begin(), cols.end());
            for (int j = 0; j < ones; ++j) {
                glass[i][cols[j]] = 1;
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(glass[i]);
    }

    return 0;
}
