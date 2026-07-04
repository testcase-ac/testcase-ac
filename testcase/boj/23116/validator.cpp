#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_N_SUM = 100000;
    constexpr int MAX_VALUE = (1 << 20) - 1;

    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalN = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= MAX_N_SUM, "sum of n exceeds %d", MAX_N_SUM);

        set<int> seen;
        for (int i = 1; i <= n; ++i) {
            int b = inf.readInt(0, MAX_VALUE, "b_i");
            ensuref(seen.insert(b).second,
                    "duplicate set element at testcase %d index %d: %d",
                    caseIndex, i, b);

            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
