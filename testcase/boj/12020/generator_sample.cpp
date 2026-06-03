#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
    } else {
        n = rnd.next(3, 10);
    }

    vector<vector<long long>> a(n, vector<long long>(n, 0));

    int limit = rnd.any(vector<int>{1, 2, 5, 10, 100});
    for (int i = 0; i < n; ++i) {
        int lo = -limit;
        int hi = limit;

        if (mode == 2 && rnd.next(0, 2) == 0) {
            lo = 0;
        }
        if (mode == 3 && rnd.next(0, 2) == 0) {
            hi = 0;
        }

        a[i][i] = rnd.next(lo, hi);
        if (i > 0) {
            a[i][i - 1] = rnd.next(-limit, limit);
        }
        if (i + 1 < n) {
            a[i][i + 1] = rnd.next(-limit, limit);
        }
    }

    if (mode == 4) {
        int row = rnd.next(0, n - 1);
        if (row > 0) {
            a[row][row - 1] = 0;
        }
        a[row][row] = 0;
        if (row + 1 < n) {
            a[row][row + 1] = 0;
        }
    }

    if (mode == 5) {
        int pos = rnd.next(0, n - 1);
        a[pos][pos] = rnd.any(vector<long long>{-1000000000LL, 1000000000LL});
        if (pos > 0) {
            a[pos][pos - 1] = rnd.next(-1000000000LL, 1000000000LL);
        }
        if (pos + 1 < n) {
            a[pos][pos + 1] = rnd.next(-1000000000LL, 1000000000LL);
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
