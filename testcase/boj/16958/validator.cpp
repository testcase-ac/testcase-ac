#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int t = inf.readInt(1, 2000, "T");
    inf.readEoln();

    set<pair<int, int>> coordinates;
    for (int i = 1; i <= n; ++i) {
        int s = inf.readInt(0, 1, "s");
        inf.readSpace();
        int x = inf.readInt(0, 1000, "x");
        inf.readSpace();
        int y = inf.readInt(0, 1000, "y");
        inf.readEoln();

        ensuref(coordinates.insert({x, y}).second,
                "duplicate city coordinate at city %d: (%d, %d)", i, x, y);
    }

    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readEoln();

        ensuref(a != b, "query %d has identical cities: %d", i, a);
    }

    inf.readEof();
}
