#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 5);
    int bMode = rnd.next(6);
    long long b;
    if (bMode == 0) {
        b = 1;
    } else if (bMode == 1) {
        b = rnd.next(2, 12);
    } else if (bMode == 2) {
        b = rnd.next(13, 1000);
    } else if (bMode == 3) {
        b = rnd.next(99999999000LL, 100000000000LL);
    } else if (bMode == 4) {
        b = 1LL << rnd.next(1, 36);
    } else {
        b = rnd.next(1LL, 100000000000LL);
    }

    vector<vector<int> > a(n, vector<int>(n, 0));
    int mode = rnd.next(7);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            a[i][i] = rnd.next(0, 1000);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i][i] = 1;
        }
        int changes = rnd.next(1, n * n);
        for (int t = 0; t < changes; ++t) {
            int r = rnd.next(n);
            int c = rnd.next(n);
            a[r][c] = rnd.next(0, 9);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                a[i][j] = rnd.next(0, 20);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(990, 1000);
            }
        }
    } else if (mode == 4) {
        int density = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(5) < density) {
                    a[i][j] = rnd.next(0, 1000);
                }
            }
        }
    } else if (mode == 5) {
        int start = rnd.next(0, 1000);
        int step = rnd.next(0, 37);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = (start + step * (i * n + j)) % 1001;
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(0, 1000);
            }
        }
    }

    println(n, b);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
