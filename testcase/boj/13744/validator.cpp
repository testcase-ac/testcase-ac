#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int radius = inf.readInt(1, 1000, "r");
    inf.readSpace();
    int l = inf.readInt(1, 1000, "l");
    inf.readEoln();

    set<pair<int, int>> lamps;
    for (int i = 0; i < l; ++i) {
        int row = inf.readInt(1, n, "r_i");
        inf.readSpace();
        int col = inf.readInt(1, n, "c_i");
        inf.readEoln();

        ensuref(lamps.insert({row, col}).second,
                "duplicate lamp at index %d: (%d, %d)", i + 1, row, col);
    }

    inf.readEof();
}
