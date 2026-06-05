#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 40320, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 20, "N");
        inf.readEoln();

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            int value = inf.readInt(1, n, "P_i");
            ensuref(!seen[value], "duplicate permutation value %d at position %d", value, i);
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
