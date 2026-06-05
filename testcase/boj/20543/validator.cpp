#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readEoln();
    ensuref(m % 2 == 1, "M must be odd: %d", m);

    vector<vector<long long>> diff(n + 1, vector<long long>(n + 1, 0));

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (c > 0) {
                inf.readSpace();
            }

            long long h = inf.readLong(-2147483648LL, 0LL, "H_rc");

            if (r > 0) {
                diff[r][c] += diff[r - 1][c];
            }
            if (c > 0) {
                diff[r][c] += diff[r][c - 1];
            }
            if (r > 0 && c > 0) {
                diff[r][c] -= diff[r - 1][c - 1];
            }

            long long damage = diff[r][c];
            long long targetDamage = -h;
            if (r <= n - m && c <= n - m) {
                long long bombs = targetDamage - damage;
                ensuref(bombs >= 0,
                        "negative bomb count needed at blast top-left (%d, %d): %lld",
                        r,
                        c,
                        bombs);

                damage += bombs;
                diff[r][c] += bombs;
                diff[r][c + m] -= bombs;
                diff[r + m][c] -= bombs;
                diff[r + m][c + m] += bombs;
            }

            ensuref(damage == targetDamage,
                    "H[%d][%d]=%lld is not realizable by valid MxM bomb blasts; expected damage %lld, got %lld",
                    r,
                    c,
                    h,
                    targetDamage,
                    damage);
        }
        inf.readEoln();
    }

    inf.readEof();
}
