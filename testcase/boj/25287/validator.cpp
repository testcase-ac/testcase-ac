#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50000, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50000, "N");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 50000, "sum of N exceeds 50000: %d", totalN);

        vector<int> seen(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                inf.readSpace();
            }

            int value = inf.readInt(1, n, "p_i");
            ensuref(!seen[value], "duplicate permutation value %d at position %d", value, i);
            seen[value] = 1;
        }
        inf.readEoln();
    }

    inf.readEof();
}
