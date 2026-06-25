#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCase = 1;
    int scalarTokens = 0;

    while (true) {
        setTestCase(testCase);

        int k = inf.readInt(0, 100, "k");
        ++scalarTokens;

        if (k == 0) {
            inf.readEoln();
            break;
        }

        inf.readSpace();
        set<int> moves;
        for (int i = 0; i < k; ++i) {
            int s = inf.readInt(1, 10000, "s_i");
            ++scalarTokens;
            ensuref(moves.insert(s).second, "duplicate move value at index %d: %d", i + 1, s);
            if (i + 1 < k) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }

        int m = inf.readInt(1, 100, "m");
        ++scalarTokens;
        inf.readEoln();

        for (int i = 0; i < m; ++i) {
            int l = inf.readInt(1, 100, "l");
            ++scalarTokens;
            inf.readSpace();

            for (int j = 0; j < l; ++j) {
                inf.readInt(0, 10000, "h_i");
                ++scalarTokens;
                if (j + 1 < l) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }

        // CHECK: the statement gives no maximum number of test cases; cap total
        // numeric tokens below the local practical limit for primarily numeric input.
        ensuref(scalarTokens < 5000000, "too many numeric tokens: %d", scalarTokens);
        ++testCase;
    }

    inf.readEof();
}
