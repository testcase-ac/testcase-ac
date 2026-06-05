#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long minPathCost(const vector<vector<int>>& a) {
    int n = (int)a.size();
    int m = (int)a[0].size();
    vector<vector<long long>> dp(n, vector<long long>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            long long best = (i == 0 && j == 0) ? 0 : (long long)4e18;
            if (i > 0) best = min(best, dp[i - 1][j]);
            if (j > 0) best = min(best, dp[i][j - 1]);
            dp[i][j] = best + a[i][j];
        }
    }
    return dp[n - 1][m - 1];
}

int boundedH(long long value) {
    value = max(1LL, min(100000000LL, value));
    return (int)value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 2);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
        if (rnd.next(2) == 0) swap(n, m);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        m = rnd.next(3, 12);
    } else if (mode == 4) {
        n = rnd.next(2, 9);
        m = rnd.next(2, 9);
    } else {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
    }

    vector<vector<int>> a(n, vector<int>(m, 0));

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(0, 8);
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(0, 20);
            }
        }
    } else if (mode == 2) {
        int openRow = rnd.next(n);
        int openCol = rnd.next(m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(20, 80);
                if (i == openRow || j == openCol) a[i][j] = rnd.next(0, 3);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(100) < 70) {
                    a[i][j] = 0;
                } else {
                    a[i][j] = rnd.next(1, 12);
                }
            }
        }
    } else if (mode == 4) {
        int base = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = base + rnd.next(0, 5);
            }
        }
        for (int k = 0; k < rnd.next(1, n + m); ++k) {
            a[rnd.next(n)][rnd.next(m)] = rnd.next(0, 2);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int bucket = rnd.next(100);
                if (bucket < 20) {
                    a[i][j] = 0;
                } else if (bucket < 85) {
                    a[i][j] = rnd.next(1, 30);
                } else {
                    a[i][j] = rnd.next(1000, 100000000);
                }
            }
        }
    }

    long long best = minPathCost(a);
    int hMode = rnd.next(0, 3);
    int h = 1;
    if (hMode == 0) {
        h = boundedH(best);
    } else if (hMode == 1) {
        h = boundedH(best - rnd.next(1, 10));
    } else if (hMode == 2) {
        h = boundedH(best + rnd.next(1, 10));
    } else {
        h = rnd.next(1, 100000000);
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }
    println(h);

    return 0;
}
