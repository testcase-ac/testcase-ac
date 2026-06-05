#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(3, 12);
    }

    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = rnd.next(1, 5);
    } else if (kMode == 1) {
        k = rnd.next(6, 100);
    } else if (kMode == 2) {
        k = rnd.next(1000, 1000000);
    } else {
        k = rnd.next(900000000, 1000000000);
    }

    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1)) {
                a[i][i] = 1;
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i + 1 < n; ++i) {
            a[i][i + 1] = 1;
        }
        if (rnd.next(0, 1)) {
            a[n - 1][0] = 1;
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next(100) < 35) {
                    a[i][j] = 1;
                }
            }
        }
    } else if (mode == 3) {
        int p = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(100) < p) {
                    a[i][j] = 1;
                }
            }
        }
    } else if (mode == 4) {
        int split = rnd.next(1, n - 1);
        int p = rnd.next(30, 85);
        for (int i = 0; i < split; ++i) {
            for (int j = split; j < n; ++j) {
                if (rnd.next(100) < p) {
                    a[i][j] = 1;
                }
                if (rnd.next(100) < p / 2) {
                    a[j][i] = 1;
                }
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i][i] = 1;
        }
        int extra = rnd.next(0, n * 2);
        for (int e = 0; e < extra; ++e) {
            a[rnd.next(n)][rnd.next(n)] = 1;
        }
    } else {
        vector<int> perm(n);
        for (int i = 0; i < n; ++i) {
            perm[i] = i;
        }
        shuffle(perm.begin(), perm.end());
        for (int i = 0; i < n; ++i) {
            a[perm[i]][perm[(i + 1) % n]] = 1;
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a[perm[i]][perm[rnd.next(n)]] = 1;
            }
        }
    }

    println(n, k);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
