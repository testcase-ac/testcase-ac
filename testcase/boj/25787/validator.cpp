#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s = inf.readInt(1, 100, "s");
    inf.readSpace();
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    set<pair<int, int>> fish;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 100, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 100, "y_i");
        inf.readEoln();

        ensuref(fish.insert({x, y}).second,
                "duplicate fish at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
