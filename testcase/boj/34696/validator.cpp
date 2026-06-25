#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50000, "M");
    inf.readEoln();

    ensuref(n <= m, "N must be at most M: N=%d, M=%d", n, m);

    set<pair<int, int>> coordinates;
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(0, 999999999, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 999999999, "y_i");
        inf.readEoln();

        ensuref(coordinates.emplace(x, y).second,
                "duplicate coordinate at seat %d: (%d, %d)", i, x, y);
    }

    inf.readInt(1, m, "s_1");
    inf.readEoln();
    inf.readEof();
}
