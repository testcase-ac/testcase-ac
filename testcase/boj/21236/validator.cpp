#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<pair<int, int>> occupied;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 1000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000, "y_i");
        inf.readEoln();

        ensuref(occupied.emplace(x, y).second,
                "duplicate cow cell at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
