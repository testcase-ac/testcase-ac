#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> current;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 100000, "current_x_i");
        inf.readSpace();
        int y = inf.readInt(1, 100000, "current_y_i");
        inf.readEoln();

        ensuref(current.insert({x, y}).second,
                "duplicate current red cell at index %d: (%d, %d)",
                i + 1, x, y);
    }

    set<pair<int, int>> target;
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, 100000, "target_x_i");
        inf.readSpace();
        int y = inf.readInt(1, 100000, "target_y_i");
        inf.readEoln();

        ensuref(target.insert({x, y}).second,
                "duplicate target red cell at index %d: (%d, %d)",
                i + 1, x, y);
    }

    inf.readEof();
}
