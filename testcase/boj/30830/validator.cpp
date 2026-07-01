#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int board = 1; board <= 2; ++board) {
        set<pair<int, int>> occupied;
        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(1, n, "x_i");
            inf.readSpace();
            int y = inf.readInt(1, n, "y_i");
            inf.readEoln();

            ensuref(occupied.insert({x, y}).second,
                    "duplicate rook on board %d at index %d: (%d, %d)",
                    board, i, x, y);
        }
    }

    inf.readEof();
}
