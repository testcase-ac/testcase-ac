#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    int maxK = min(n * m - 2, 10000);
    int k = inf.readInt(0, maxK, "K");
    inf.readEoln();

    set<pair<int, int>> holes;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, m, "y_i");
        inf.readEoln();

        ensuref(!(x == 1 && y == 1), "hole %d is at the start cell", i + 1);
        ensuref(!(x == n && y == m), "hole %d is at the destination cell", i + 1);
        ensuref(holes.emplace(x, y).second, "duplicate hole at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
