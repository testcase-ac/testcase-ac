#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using Matrix = vector<vector<int>>;
using Longs = vector<long long>;

static Longs arbitraryTarget(int n);

static Matrix makeMoves(int n, int mode) {
    Matrix a(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        a[i][i] = 1;
        for (int j = i + 1; j < n; ++j) {
            if (mode == 0) {
                a[i][j] = 0;
            } else if (mode == 1) {
                a[i][j] = rnd.next(-3, 3);
            } else if (mode == 2) {
                a[i][j] = rnd.any(vector<int>{-1000, -7, -1, 0, 1, 7, 1000});
            } else {
                a[i][j] = (rnd.next(3) == 0 ? rnd.next(-20, 20) : 0);
            }
        }
    }
    return a;
}

static Longs reachableTarget(const Matrix& a) {
    int n = int(a.size());
    for (int attempt = 0; attempt < 100; ++attempt) {
        Longs count(n), y(n, 0);
        int scale = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            if (scale == 0) {
                count[i] = rnd.next(0, 8);
            } else if (scale == 1) {
                count[i] = rnd.next(0, 2000);
            } else {
                count[i] = rnd.next(0, 1000000);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                y[j] += 1LL * a[i][j] * count[i];
            }
        }

        if (*min_element(y.begin(), y.end()) >= -500000000LL &&
            *max_element(y.begin(), y.end()) <= 500000000LL) {
            return y;
        }
    }

    return arbitraryTarget(n);
}

static Longs arbitraryTarget(int n) {
    Longs y(n);
    int mode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            y[i] = rnd.next(-10, 10);
        } else if (mode == 1) {
            y[i] = rnd.next(-1000000, 1000000);
        } else if (mode == 2) {
            y[i] = rnd.any(vector<long long>{-500000000LL, -1LL, 0LL, 1LL, 500000000LL});
        } else {
            y[i] = rnd.next(-500000000, 500000000);
        }
    }
    return y;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 8);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 8);
        }

        int matrixMode = rnd.next(0, 3);
        Matrix a = makeMoves(n, matrixMode);
        Longs y = (rnd.next(2) == 0 ? reachableTarget(a) : arbitraryTarget(n));

        println(n);
        for (const auto& row : a) {
            println(row);
        }
        println(y);
    }

    return 0;
}
