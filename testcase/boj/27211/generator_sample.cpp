#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(2, 18);
    int m = rnd.next(2, 18);
    if (rnd.next(4) == 0) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 6);
    }

    vector<vector<int>> a(n, vector<int>(m, 1));

    if (mode == 0) {
        int p = rnd.next(15, 85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(100) < p ? 0 : 1;
            }
        }
    } else if (mode == 1) {
        int p = rnd.next(10, 45);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(100) < p ? 1 : 0;
            }
        }
    } else if (mode == 2) {
        bool vertical = rnd.next(2);
        int period = rnd.next(2, 4);
        int openResidue = rnd.next(period);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int index = vertical ? j : i;
                a[i][j] = index % period == openResidue ? 0 : rnd.next(4) == 0;
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = (i + j + rnd.next(2)) % 2;
            }
        }
    } else if (mode == 4) {
        int row = rnd.next(n);
        int col = rnd.next(m);
        for (int j = 0; j < m; ++j) {
            a[row][j] = 0;
        }
        for (int i = 0; i < n; ++i) {
            a[i][col] = 0;
        }
        for (int k = 0; k < rnd.next(1, n + m); ++k) {
            a[rnd.next(n)][rnd.next(m)] = 0;
        }
    } else if (mode == 5) {
        int blocks = rnd.next(2, 6);
        for (int b = 0; b < blocks; ++b) {
            int r0 = rnd.next(n);
            int c0 = rnd.next(m);
            int h = rnd.next(1, min(n, 4));
            int w = rnd.next(1, min(m, 4));
            for (int dr = 0; dr < h; ++dr) {
                for (int dc = 0; dc < w; ++dc) {
                    a[(r0 + dr) % n][(c0 + dc) % m] = 0;
                }
            }
        }
    } else if (mode == 6) {
        fill(a.begin(), a.end(), vector<int>(m, 0));
    } else {
        fill(a.begin(), a.end(), vector<int>(m, 1));
        a[rnd.next(n)][rnd.next(m)] = 0;
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
