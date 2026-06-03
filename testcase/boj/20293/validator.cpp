#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(2, 3000, "R");
    inf.readSpace();
    int c = inf.readInt(2, 3000, "C");
    inf.readEoln();

    int n = inf.readInt(0, 1000, "N");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 1; i <= n; ++i) {
        int row = inf.readInt(1, r, "r_i");
        inf.readSpace();
        int col = inf.readInt(1, c, "c_i");
        inf.readSpace();
        inf.readInt(0, 100, "f_i");
        inf.readEoln();

        ensuref(!(row == 1 && col == 1),
                "fuel storage %d is at the starting position", i);
        ensuref(!(row == r && col == c),
                "fuel storage %d is at the pyramid position", i);
        ensuref(positions.insert({row, col}).second,
                "duplicate fuel storage position at index %d: (%d, %d)", i, row, col);
    }

    inf.readEof();
}
