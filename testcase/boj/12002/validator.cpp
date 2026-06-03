#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 50000, "n");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 40000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 40000, "y_i");
        inf.readEoln();

        ensuref(positions.insert({x, y}).second,
                "duplicate cow position at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
