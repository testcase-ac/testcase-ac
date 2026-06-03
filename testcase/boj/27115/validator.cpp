#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 3000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 300000, "K");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 1; i <= k; ++i) {
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        int x = inf.readInt(1, m, "x_i");
        inf.readSpace();
        inf.readInt(1, 3000, "p_i");
        inf.readEoln();

        ensuref(positions.emplace(y, x).second,
                "duplicate communication station position at index %d: (%d, %d)",
                i, y, x);
    }

    inf.readEof();
}
