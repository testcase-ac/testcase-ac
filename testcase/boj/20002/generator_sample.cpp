#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else if (mode == 3) {
        n = rnd.next(10, 25);
    } else if (mode == 4) {
        n = rnd.next(20, 40);
    } else if (mode == 5) {
        n = rnd.next(50, 90);
    } else {
        n = rnd.next(250, 300);
    }

    vector<vector<int>> profit(n, vector<int>(n));
    if (mode == 0) {
        profit[0][0] = rnd.next(-1000, 1000);
    } else if (mode == 1) {
        int lo = rnd.next(-1000, -1);
        int hi = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                profit[i][j] = rnd.next(lo, hi);
            }
        }
    } else if (mode == 2) {
        int base = rnd.next(-30, 30);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                profit[i][j] = base + rnd.next(-20, 20);
            }
        }
    } else if (mode == 3) {
        int sign = rnd.next(0, 1) == 0 ? -1 : 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                profit[i][j] = sign * rnd.next(0, 1000);
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int value = rnd.next(-25, 25);
                if (rnd.next(0, 9) == 0) value = rnd.next(-1000, 1000);
                profit[i][j] = value;
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                profit[i][j] = ((i + j + rnd.next(0, 1)) % 2 == 0)
                                   ? rnd.next(500, 1000)
                                   : rnd.next(-1000, -500);
            }
        }
    } else {
        int lo = rnd.next(-3, 0);
        int hi = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                profit[i][j] = rnd.next(lo, hi);
            }
        }
    }

    if (n >= 3 && rnd.next(0, 2) == 0) {
        int len = rnd.next(1, n);
        int r = rnd.next(0, n - len);
        int c = rnd.next(0, n - len);
        int bonus = rnd.next(20, 1000);
        if (rnd.next(0, 1) == 0) bonus = -bonus;
        for (int i = r; i < r + len; ++i) {
            for (int j = c; j < c + len; ++j) {
                profit[i][j] = bonus;
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(profit[i]);
    }

    return 0;
}
