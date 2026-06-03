#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 5);
    int mode = rnd.next(0, 5);
    long long b;
    vector<vector<int>> a(n, vector<int>(n, 0));

    if (mode == 0) {
        b = rnd.any(vector<long long>{1, 2, 3, 10, 100000000000LL});
        for (int i = 0; i < n; ++i) {
            a[i][i] = rnd.any(vector<int>{0, 1, 999, 1000});
            if (rnd.next(0, 3) == 0) {
                a[i][(i + 1) % n] = rnd.next(0, 1000);
            }
        }
    } else if (mode == 1) {
        b = rnd.next(1LL, 100000000000LL);
        int hi = rnd.any(vector<int>{1, 2, 10, 999, 1000});
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.next(0, hi);
            }
        }
    } else if (mode == 2) {
        b = rnd.any(vector<long long>{1, 5, 31, 1024, 99999999999LL});
        int nonZero = rnd.next(n, n * n);
        for (int k = 0; k < nonZero; ++k) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            a[i][j] = rnd.any(vector<int>{1, 2, 999, 1000});
        }
    } else if (mode == 3) {
        b = rnd.next(1LL, 100000000000LL);
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                a[i][j] = rnd.next(0, 1000);
            }
        }
    } else if (mode == 4) {
        b = rnd.any(vector<long long>{2, 3, 4, 99991, 100000000000LL});
        int rowBase = rnd.next(0, 1000);
        int colStep = rnd.next(0, 250);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = (rowBase + i * rnd.next(0, 20) + j * colStep) % 1001;
            }
        }
    } else {
        b = rnd.next(1LL, 100000000000LL);
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
