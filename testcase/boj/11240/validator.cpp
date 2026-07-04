#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        set<pair<int, int>> flowers;
        for (int i = 1; i <= n; ++i) {
            int r = inf.readInt(1, 1000000, "r_i");
            inf.readSpace();
            int c = inf.readInt(1, 1000000, "c_i");
            inf.readEoln();

            ensuref(flowers.insert({r, c}).second,
                    "duplicate flower in test case %d at index %d: (%d, %d)",
                    tc, i, r, c);
        }
    }

    inf.readEof();
}
