#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = 1;
        if (mode == 0) {
            n = 1;
        } else if (mode == 1) {
            n = rnd.next(2, 4);
        } else {
            n = rnd.next(3, 12);
        }

        vector<vector<int>> a(n, vector<int>(n, 0));
        int small_hi = rnd.next(3, 40);

        if (mode == 0) {
            a[0][0] = rnd.next(0, 10000000);
        } else if (mode == 1) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] = rnd.next(0, small_hi);
                }
            }
        } else if (mode == 2) {
            int d = rnd.next(-(n - 1), n - 1);
            int base = rnd.next(1, small_hi);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (j - i == d) {
                        a[i][j] = rnd.next(base, min(10000000, base + small_hi));
                    } else {
                        a[i][j] = rnd.next(0, 2);
                    }
                }
            }
        } else if (mode == 3) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] = ((i + j) % 2 == 0) ? rnd.next(0, small_hi) : 0;
                }
            }
        } else if (mode == 4) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] = rnd.next(0, 1) ? rnd.next(0, small_hi) : 0;
                }
            }
            int spikes = rnd.next(1, n);
            for (int k = 0; k < spikes; ++k) {
                a[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = rnd.next(9999990, 10000000);
            }
        } else {
            int offset = rnd.next(0, n - 1);
            int diagonal_hi = max(5, small_hi);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] = (j == (i + offset) % n) ? rnd.next(5, diagonal_hi) : rnd.next(0, 3);
                }
            }
        }

        println(n);
        for (int i = 0; i < n; ++i) {
            println(a[i]);
        }
    }

    return 0;
}
