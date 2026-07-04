#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 100000, "P_lr");
    inf.readSpace();
    inf.readInt(1, 100000, "P_j");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(-1000000000, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 1000000000, "y_i");
        inf.readEoln();

        ensuref(positions.insert({x, y}).second,
                "duplicate money position at index %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
}
