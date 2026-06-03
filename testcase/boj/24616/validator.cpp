#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<pair<int, int>> locations;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 1000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 10, "y_i");
        inf.readEoln();

        ensuref(locations.insert({x, y}).second,
                "duplicate cow location at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
