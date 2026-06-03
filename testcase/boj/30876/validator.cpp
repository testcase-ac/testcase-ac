#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    set<pair<int, int>> stations;
    int minY = 1001;
    int minYCount = 0;

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(-1000, 1000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000, 1000, "y_i");
        inf.readEoln();

        ensuref(stations.insert({x, y}).second,
                "duplicate station at index %d: (%d, %d)", i, x, y);

        if (y < minY) {
            minY = y;
            minYCount = 1;
        } else if (y == minY) {
            ++minYCount;
        }
    }

    ensuref(minYCount == 1,
            "the southernmost point is not unique: %d stations have minimum y=%d",
            minYCount, minY);

    inf.readEof();
}
