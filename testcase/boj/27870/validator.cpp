#include "testlib.h"

#include <set>
#include <tuple>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 10000, "M");
    inf.readEoln();

    set<tuple<int, int, int, int>> forbidden;
    for (int i = 1; i <= m; ++i) {
        int p = inf.readInt(1, 4, "p");
        inf.readSpace();
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int q = inf.readInt(1, 4, "q");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(p < q, "pair %d has p >= q: p=%d q=%d", i, p, q);
        ensuref(forbidden.emplace(p, x, q, y).second,
                "duplicate forbidden pair at line %d: (%d, %d, %d, %d)",
                i + 1, p, x, q, y);
    }

    inf.readEof();
}
