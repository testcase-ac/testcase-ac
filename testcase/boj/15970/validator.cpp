#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "N");
    inf.readEoln();

    set<int> positions;
    vector<int> colorCount(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 100000, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "duplicate position at point %d: %d", i + 1, x);
        ++colorCount[y];
    }

    for (int color = 1; color <= n; ++color) {
        ensuref(colorCount[color] == 0 || colorCount[color] >= 2,
                "color %d appears exactly once", color);
    }

    inf.readEof();
    return 0;
}
