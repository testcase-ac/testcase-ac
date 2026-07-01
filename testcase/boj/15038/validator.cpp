#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tvX = inf.readInt(-1000000, 1000000, "T_X");
    inf.readSpace();
    int tvY = inf.readInt(-1000000, 1000000, "T_Y");
    inf.readEoln();

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    set<pair<int, int>> points;
    points.insert({tvX, tvY});
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000000, 1000000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "Y_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "H_i");
        inf.readEoln();

        ensuref(points.insert({x, y}).second,
                "duplicate coordinates at lizard %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
    return 0;
}
