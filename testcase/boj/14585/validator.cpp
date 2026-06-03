#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 300, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "M");
    inf.readEoln();

    set<pair<int, int>> seen;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, 300, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 300, "y_i");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "basket %d is at the origin", i);
        ensuref(seen.insert({x, y}).second,
                "duplicate basket position at index %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
    return 0;
}
