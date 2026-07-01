#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 1;
    while (true) {
        int n = inf.readInt(0, 100, "N");
        inf.readSpace();
        int m = inf.readInt(0, 100, "M");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        setTestCase(caseIndex++);
        ensuref(n >= 1, "N must be positive in a non-terminal test case");
        ensuref(m >= 1, "M must be positive in a non-terminal test case");

        int maxK = n * m;
        int minK = maxK - 50;
        int k = inf.readInt(minK, maxK, "K");
        inf.readEoln();

        set<pair<int, int>> ponds;
        for (int i = 0; i < k; ++i) {
            int x = inf.readInt(1, n, "X");
            inf.readSpace();
            int y = inf.readInt(1, m, "Y");
            inf.readEoln();

            // CHECK: K describes squares turned into ponds, so repeated coordinates
            // would not describe K distinct pond squares.
            ensuref(ponds.insert({x, y}).second,
                    "duplicate pond coordinate at index %d: (%d, %d)", i + 1, x, y);
        }
    }

    inf.readEof();
}
