#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    vector<int> s = inf.readInts(n, 0, 100000, "S_i");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        long long rowSum = 0;
        for (int j = 0; j < n + m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            int t = inf.readInt(0, 100000, "T_i_j");
            ensuref(i != j || t == 0,
                    "T_%d_%d must be 0, got %d",
                    i + 1,
                    j + 1,
                    t);
            rowSum += t;
        }
        inf.readEoln();

        ensuref(rowSum <= s[i],
                "sum of row %d must be <= S_%d (%d), got %lld",
                i + 1,
                i + 1,
                s[i],
                rowSum);
    }

    inf.readEof();
}
