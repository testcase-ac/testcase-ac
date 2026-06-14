#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, 1000000, "x");
        inf.readSpace();
        int y = inf.readInt(0, 1000000, "y");
        inf.readSpace();
        inf.readInt(1, 7000, "v");
        inf.readEoln();

        ensuref(positions.insert({x, y}).second,
                "duplicate swallow position at row %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
}
