#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int largeCases = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int l = inf.readInt(1, 1000000000, "L");
        inf.readEoln();

        ensuref(n < l, "N must be less than L, found N=%d L=%d", n, l);
        if (n > 1000) {
            ++largeCases;
        }

        set<int> positions;
        for (int i = 1; i <= n; ++i) {
            int p = inf.readInt(1, l - 1, "P_i");
            inf.readSpace();
            inf.readInt(0, 1, "D_i");
            inf.readEoln();

            ensuref(positions.insert(p).second,
                    "duplicate position at ant %d: %d", i, p);
        }
    }

    ensuref(largeCases <= 15,
            "at most 15 test cases may have N > 1000, found %d",
            largeCases);

    inf.readEof();
}
