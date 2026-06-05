#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "k");
    inf.readEoln();

    long long maxPieces = min(1LL * n * n, 100000LL);
    ensuref(k <= maxPieces, "k must be at most min(n^2, 100000), got k=%d n=%d", k, n);

    set<pair<int, int>> occupied;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        ensuref(occupied.emplace(x, y).second,
                "duplicate dabbaba position at index %d: (%d, %d)",
                i + 1,
                x,
                y);
    }

    inf.readEof();
}
