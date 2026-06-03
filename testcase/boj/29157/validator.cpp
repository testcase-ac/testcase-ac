#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int k = inf.readInt(0, 20, "K");
    inf.readEoln();

    set<pair<int, int>> bombs;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(0, n, "X_i");
        inf.readSpace();
        int y = inf.readInt(0, m, "Y_i");
        inf.readEoln();

        ensuref(!(x == 0 && y == 0), "bomb %d is at the start point", i + 1);
        ensuref(!(x == n && y == m), "bomb %d is at the destination point", i + 1);
        ensuref(bombs.insert({x, y}).second, "duplicate bomb at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
