#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);

    if (mode == 4) {
        n = rnd.next(3, 9);
        m = rnd.next(3, 9);
    } else if (mode == 6) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    }

    vector<vector<long long>> a(n, vector<long long>(m, 0));

    if (mode == 0) {
        long long hi = rnd.next(0, 12);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(0LL, hi);
            }
        }
    } else if (mode == 1) {
        long long h = rnd.next(1LL, 30LL);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = h;
            }
        }
    } else if (mode == 2) {
        long long outer = rnd.next(0LL, 5LL);
        long long inner = rnd.next(outer, outer + 20);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool border = i == 0 || i + 1 == n || j == 0 || j + 1 == m;
                a[i][j] = border ? outer : inner + rnd.next(0LL, 5LL);
            }
        }
    } else if (mode == 3) {
        long long base = rnd.next(0LL, 8LL);
        long long rowStep = rnd.next(0LL, 4LL);
        long long colStep = rnd.next(0LL, 4LL);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = base + rowStep * i + colStep * j;
            }
        }
    } else if (mode == 4) {
        long long low = rnd.next(0LL, 3LL);
        long long high = rnd.next(8LL, 35LL);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = ((i + j + rnd.next(0, 1)) % 2 == 0) ? low : high;
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next(0, 3) == 0 ? 0 : rnd.next(1LL, 20LL);
            }
        }
    } else {
        long long h = 1000000000LL - rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = max(0LL, h - rnd.next(0LL, 3LL));
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
