#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int k = inf.readInt(2, 100000, "K");
    inf.readEoln();

    ensuref(k <= n * n, "K=%d exceeds the number of cells in a %d by %d grid", k, n, n);

    set<pair<int, int>> origins;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(origins.insert({x, y}).second,
                "duplicate civilization origin at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
