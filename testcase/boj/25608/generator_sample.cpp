#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int nextNonZero(int lo, int hi) {
    int x = 0;
    while (x == 0) {
        x = rnd.next(lo, hi);
    }
    return x;
}

vector<int> makeRow(int m, int mode) {
    vector<int> row(m);

    if (mode == 0) {
        for (int &x : row) {
            x = rnd.next(-100, 0);
        }
    } else if (mode == 1) {
        for (int &x : row) {
            x = rnd.next(-5, 25);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, max(1, m - 1));
        for (int i = 0; i < m; ++i) {
            row[i] = (i < split ? rnd.next(3, 35) : rnd.next(-40, 5));
        }
    } else if (mode == 3) {
        int split = rnd.next(1, max(1, m - 1));
        for (int i = 0; i < m; ++i) {
            row[i] = (i < split ? rnd.next(-40, 5) : rnd.next(3, 35));
        }
    } else {
        int bias = rnd.any(vector<int>{-20, -8, 0, 8, 20});
        for (int &x : row) {
            x = max(-100, min(100, bias + rnd.next(-25, 25)));
            if (rnd.next(5) == 0) {
                x = rnd.any(vector<int>{-100, -50, 0, 50, 100});
            }
        }
    }

    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pattern = rnd.next(0, 5);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 18);

    if (pattern == 4 && rnd.next(3) == 0) {
        m = rnd.next(50, 120);
    }

    vector<vector<int>> a(n);
    for (int i = 0; i < n; ++i) {
        int mode;
        if (pattern == 0) {
            mode = 0;
        } else if (pattern == 1) {
            mode = rnd.next(0, 1);
        } else if (pattern == 2) {
            mode = (i % 2 == 0 ? 2 : 3);
        } else if (pattern == 3) {
            mode = rnd.next(2, 3);
        } else {
            mode = rnd.next(0, 4);
        }
        a[i] = makeRow(m, mode);
    }

    if (pattern == 3 && n >= 3 && m >= 3) {
        a[0][0] = nextNonZero(30, 100);
        a[0][m - 1] = rnd.next(-100, -30);
        a[1][0] = rnd.next(-100, -30);
        a[1][m - 1] = nextNonZero(30, 100);
        a[2][0] = nextNonZero(20, 80);
        a[2][m - 1] = nextNonZero(20, 80);
    }

    shuffle(a.begin(), a.end());

    println(n, m);
    for (const vector<int> &row : a) {
        println(row);
    }

    return 0;
}
