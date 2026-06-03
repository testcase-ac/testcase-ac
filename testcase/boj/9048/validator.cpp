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

        int f = inf.readInt(1, 30, "F");
        inf.readSpace();
        int r = inf.readInt(1, 30, "R");
        inf.readSpace();
        int n = inf.readInt(0, f * r, "N");
        inf.readEoln();

        set<pair<int, int>> offices;
        for (int i = 1; i <= n; ++i) {
            int a = inf.readInt(1, f, "a");
            inf.readSpace();
            int b = inf.readInt(1, r, "b");
            inf.readEoln();

            ensuref(offices.insert({a, b}).second,
                    "duplicate lit office at index %d: (%d, %d)", i, a, b);
        }
    }

    inf.readEof();
}
