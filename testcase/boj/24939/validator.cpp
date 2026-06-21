#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "M");
    inf.readEoln();

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    long long xl = 1, xr = n, yl = 1, yr = m;
    for (int i = 1; i <= q; ++i) {
        long long x = inf.readLong(1LL, n, "x_i");
        inf.readSpace();
        long long y = inf.readLong(1LL, m, "y_i");
        inf.readSpace();
        int d = inf.readInt(1, 9, "d_i");
        inf.readEoln();

        if (d == 1) {
            xl = max(xl, x + 1);
            yl = max(yl, y);
            yr = min(yr, y);
        } else if (d == 2) {
            xr = min(xr, x - 1);
            yl = max(yl, y);
            yr = min(yr, y);
        } else if (d == 3) {
            xl = max(xl, x);
            xr = min(xr, x);
            yr = min(yr, y - 1);
        } else if (d == 4) {
            xl = max(xl, x);
            xr = min(xr, x);
            yl = max(yl, y + 1);
        } else if (d == 5) {
            xl = max(xl, x + 1);
            yl = max(yl, y + 1);
        } else if (d == 6) {
            xr = min(xr, x - 1);
            yl = max(yl, y + 1);
        } else if (d == 7) {
            xl = max(xl, x + 1);
            yr = min(yr, y - 1);
        } else if (d == 8) {
            xr = min(xr, x - 1);
            yr = min(yr, y - 1);
        } else {
            xl = max(xl, x);
            xr = min(xr, x);
            yl = max(yl, y);
            yr = min(yr, y);
        }
    }

    ensuref(xl <= xr && yl <= yr, "at least one candidate cell must exist");
    inf.readEof();
}
