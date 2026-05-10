#include "testlib.h"
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 3000, "N");
    inf.readEoln();

    // 2. For each gold mine, read x, y, w
    set<pair<int, int>> coords;
    bool has_positive = false;
    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000000000, "y_i");
        inf.readSpace();
        int w = inf.readInt(-1000000000, 1000000000, "w_i");
        inf.readEoln();

        // Check for unique coordinates
        ensuref(coords.count({x, y}) == 0, 
            "Duplicate coordinates at line %d: (%d, %d)", i+2, x, y);
        coords.insert({x, y});

        // At least one w_i > 0
        if (w > 0) has_positive = true;
    }
    ensuref(has_positive, "There must be at least one gold mine with w_i > 0");

    inf.readEof();
}
