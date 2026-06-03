#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readEoln();

    vector<vector<long long>> r(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (j > i) {
                inf.readSpace();
            }
            r[i][j] = inf.readLong(0LL, 1000000000LL, "r_ij");
        }
        inf.readEoln();
    }
    inf.readEof();

    for (int i = 0; i < n; ++i) {
        ensuref(r[i][i] == 0, "r[%d][%d] must be 0, found %lld", i + 1, i + 1, r[i][i]);
    }

    vector<long long> a(n, 0);
    for (int i = 1; i < n; ++i) {
        long long delta = r[i - 1][i];
        bool found = false;

        for (long long candidate : {a[i - 1] - delta, a[i - 1] + delta}) {
            a[i] = candidate;
            long long mn = a[i];
            long long mx = a[i];
            bool ok = true;

            for (int j = i; j >= 0; --j) {
                mn = min(mn, a[j]);
                mx = max(mx, a[j]);
                if (mx - mn != r[j][i]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                found = true;
                break;
            }
        }

        ensuref(found, "no array prefix realizes ranges ending at index %d", i + 1);
    }

    for (int i = 0; i < n; ++i) {
        long long mn = a[i];
        long long mx = a[i];
        for (int j = i; j < n; ++j) {
            mn = min(mn, a[j]);
            mx = max(mx, a[j]);
            ensuref(mx - mn == r[i][j],
                    "range mismatch for [%d, %d]: expected %lld, reconstructed %lld",
                    i + 1,
                    j + 1,
                    r[i][j],
                    mx - mn);
        }
    }
}
