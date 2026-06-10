#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 200000, "T");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> location(n + 1, 1);
    for (int i = 1; i <= t; ++i) {
        int line = inf.readInt(i, i, "line_number");
        inf.readSpace();
        int player = inf.readInt(1, n, "player");
        inf.readSpace();
        string action = inf.readToken("M|F|C|A", "action");
        inf.readSpace();

        if (action == "M") {
            int next = inf.readInt(1, 53, "destination");
            ensuref(next != location[player],
                    "line %d: player %d moves to current region %d",
                    line, player, next);
            location[player] = next;
        } else if (action == "F") {
            inf.readInt(1, 53, "item");
        } else if (action == "C") {
            int first = inf.readInt(1, 53, "first_item");
            inf.readSpace();
            int second = inf.readInt(1, 53, "second_item");
            ensuref(first != second,
                    "line %d: crafting uses the same item type %d twice",
                    line, first);
        } else {
            int target = inf.readInt(1, n, "target");
            ensuref(target != player,
                    "line %d: player %d attacks themself",
                    line, player);
        }

        inf.readEoln();
    }

    inf.readEof();
}
