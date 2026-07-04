#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 1; i <= n; ++i) {
        // CHECK: The description mentions 1e9, but the Limit section gives 1e5.
        int x = inf.readInt(-100000, 100000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-100000, 100000, "y_i");
        inf.readEoln();

        ensuref(points.emplace(x, y).second,
                "duplicate point at index %d: (%d, %d)", i, x, y);
    }

    inf.readEof();
}
