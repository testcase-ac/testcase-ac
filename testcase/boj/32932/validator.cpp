#include "testlib.h"

#include <set>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int k = inf.readInt(1, 500, "K");
    inf.readEoln();

    set<pair<int, int>> obstacles;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-500, 500, "x_i");
        inf.readSpace();
        int y = inf.readInt(-500, 500, "y_i");
        inf.readEoln();

        ensuref(x != 0 || y != 0, "obstacle %d is at the origin", i + 1);
        ensuref(obstacles.insert({x, y}).second,
                "duplicate obstacle at index %d: (%d, %d)", i + 1, x, y);
    }

    string commands = inf.readToken("[UDRL]{1,500}", "commands");
    ensuref((int)commands.size() == k,
            "command length is %d, expected K=%d", (int)commands.size(), k);
    inf.readEoln();

    inf.readEof();
}
