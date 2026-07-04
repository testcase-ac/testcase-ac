#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<pair<int, int>> coordinates;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, 100000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 100000, "y_i");
        inf.readSpace();
        inf.readInt(1, 2, "a_i");
        inf.readEoln();

        ensuref(coordinates.insert({x, y}).second,
                "duplicate pylon coordinates at line %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
