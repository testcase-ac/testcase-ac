#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 500000, "T");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200000, "N");
        inf.readEoln();
        sumN += n;
        ensuref(sumN <= 500000, "sum of N exceeds 500000 at test case %d", tc);

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            int value = inf.readInt(1, n, "A_i");
            ensuref(!seen[value], "duplicate value %d at test case %d, index %d", value, tc, i);
            seen[value] = true;

            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
