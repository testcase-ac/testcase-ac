#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long total_n = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();
        total_n += n;
        ensuref(total_n <= 500000, "sum of N exceeds 500000 at test case %d", tc);

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            int p = inf.readInt(1, n, "P_i");
            ensuref(!seen[p], "P is not a permutation: value %d appears more than once", p);
            seen[p] = true;

            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
