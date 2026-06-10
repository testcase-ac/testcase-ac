#include "testlib.h"

#include <set>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    string commands = inf.readToken("[RUX]{1,100000}", "commands");
    ensuref((int)commands.size() == n,
            "commands length must equal N: expected %d, got %d",
            n,
            (int)commands.size());
    inf.readEoln();

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    set<pair<int, int>> points;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, 500000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 500000, "y_i");
        inf.readEoln();

        ensuref(points.emplace(x, y).second,
                "duplicate point at index %d: (%d, %d)",
                i + 1,
                x,
                y);
    }

    inf.readEof();
}
