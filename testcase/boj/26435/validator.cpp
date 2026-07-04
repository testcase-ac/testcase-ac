#include "testlib.h"

#include <set>
#include <utility>

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
        inf.readInt(0, 1000000000, "E");
        inf.readEoln();

        if (n > 10000) {
            ++largeCases;
        }

        set<pair<int, int>> positions;
        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(0, 100000, "X_i");
            inf.readSpace();
            int y = inf.readInt(0, 1000000000, "Y_i");
            inf.readSpace();
            inf.readInt(1, 1000000000, "C_i");
            inf.readEoln();

            ensuref(positions.insert({x, y}).second,
                    "duplicate flower position in case %d at flower %d: (%d, %d)",
                    tc, i, x, y);
        }
    }

    ensuref(largeCases <= 10, "more than 10 cases have N greater than 10000: %d",
            largeCases);

    inf.readEof();
}
