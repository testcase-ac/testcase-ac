#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "n");
    inf.readEoln();

    set<pair<int, int>> occupied;
    for (int i = 1; i <= n; ++i) {
        int x1 = inf.readInt(1, 10000, format("x1[%d]", i));
        inf.readSpace();
        int y1 = inf.readInt(1, 10000, format("y1[%d]", i));
        inf.readSpace();
        int x2 = inf.readInt(1, 10000, format("x2[%d]", i));
        inf.readSpace();
        int y2 = inf.readInt(1, 10000, format("y2[%d]", i));
        inf.readEoln();

        int distance = abs(x1 - x2) + abs(y1 - y2);
        ensuref(distance == 1,
                "domino %d endpoints must occupy neighboring grid positions: (%d, %d) and (%d, %d)",
                i,
                x1,
                y1,
                x2,
                y2);

        ensuref(occupied.insert({x1, y1}).second,
                "grid position (%d, %d) is occupied by more than one domino",
                x1,
                y1);
        ensuref(occupied.insert({x2, y2}).second,
                "grid position (%d, %d) is occupied by more than one domino",
                x2,
                y2);
    }

    inf.readEof();
}
