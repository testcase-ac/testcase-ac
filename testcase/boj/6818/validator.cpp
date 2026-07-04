#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 30000, "M");
    inf.readEoln();
    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();
    int k = inf.readInt(1, 1000, "K");
    inf.readEoln();

    set<pair<int, int>> stations;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, m, "y");
        inf.readSpace();
        inf.readInt(1, 30000, "R");
        inf.readSpace();
        inf.readInt(1, 1000, "B");
        inf.readEoln();

        ensuref(stations.insert({x, y}).second,
                "duplicate wireless station at coffee shop (%d, %d)", x, y);
    }

    inf.readEof();
}
