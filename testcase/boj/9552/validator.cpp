#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int l = inf.readInt(1, 1000, "L");
        inf.readSpace();
        int n = inf.readInt(0, 12, "N");
        inf.readEoln();

        set<pair<int, int>> forbidden;
        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(1, 3, "X");
            inf.readSpace();
            int y = inf.readInt(1, 4, "Y");
            inf.readEoln();

            ensuref(forbidden.insert({x, y}).second,
                    "duplicate forbidden point in test case %d at index %d: (%d, %d)",
                    tc, i, x, y);
        }
    }

    inf.readEof();
}
