#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<pair<int, int>> locations;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, 1000000, "x");
        inf.readSpace();
        int y = inf.readInt(1, 1000000, "y");
        inf.readEoln();

        ensuref(x % 2 == 1, "x at cow %d must be odd, got %d", i, x);
        ensuref(y % 2 == 1, "y at cow %d must be odd, got %d", i, y);
        ensuref(locations.insert({x, y}).second,
                "duplicate cow location at cow %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
}
