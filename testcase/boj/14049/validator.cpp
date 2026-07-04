#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> required;
    for (int i = 1; i <= m; ++i) {
        int r = inf.readInt(1, n, "r_i");
        inf.readSpace();
        int c = inf.readInt(1, r, "c_i");
        inf.readEoln();

        ensuref(required.insert({r, c}).second,
                "duplicate required block at index %d: (%d, %d)", i, r, c);
    }

    inf.readEof();
}
