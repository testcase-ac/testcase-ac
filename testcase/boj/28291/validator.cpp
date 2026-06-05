#include "testlib.h"

#include <set>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 50, "W");
    inf.readSpace();
    int h = inf.readInt(1, 50, "H");
    inf.readEoln();

    int n = inf.readInt(1, w * h, "N");
    inf.readEoln();

    set<pair<int, int>> occupied;
    bool hasLamp = false;

    for (int i = 0; i < n; ++i) {
        string b = inf.readToken("redstone_dust|redstone_block|redstone_lamp", "B");
        inf.readSpace();
        int x = inf.readInt(0, w - 1, "X");
        inf.readSpace();
        int y = inf.readInt(0, h - 1, "Y");
        inf.readEoln();

        hasLamp |= b == "redstone_lamp";

        // CHECK: A W x H map with N circuit blocks is interpreted as at most one block per cell.
        ensuref(occupied.insert({x, y}).second,
                "duplicate circuit block position at line %d: (%d, %d)", i + 3, x, y);
    }

    ensuref(hasLamp, "input must contain at least one redstone_lamp");

    inf.readEof();
}
