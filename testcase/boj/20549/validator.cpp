#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 50, "N");
    inf.readEoln();

    inf.readInt(1, 50, "A");
    inf.readSpace();
    inf.readInt(1, 50, "B");
    inf.readSpace();
    inf.readInt(1, 50, "C");
    inf.readEoln();

    int startX = inf.readInt(0, n - 1, "X");
    inf.readSpace();
    int startY = inf.readInt(0, n - 1, "Y");
    inf.readEoln();

    set<pair<int, int>> positions;
    positions.insert({startX, startY});

    int m = inf.readInt(1, 4, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(0, n - 1, "X_i");
        inf.readSpace();
        int y = inf.readInt(0, n - 1, "Y_i");
        inf.readEoln();

        ensuref(positions.insert({x, y}).second,
                "start and food positions must be pairwise distinct: (%d, %d)",
                x, y);
    }

    inf.readEof();
}
