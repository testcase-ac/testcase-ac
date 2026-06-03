#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<pair<int, int>> positions;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-1000000, 1000000, "x");
        inf.readSpace();
        int y = inf.readInt(-1000000, 1000000, "y");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "balloon %d is at the origin", i + 1);
        ensuref(positions.insert({x, y}).second,
                "duplicate balloon position at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
