#include "testlib.h"

#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 1500, "m");
    inf.readSpace();
    int n = inf.readInt(1, 1500, "n");
    inf.readSpace();
    int k = inf.readInt(0, 75000, "k");
    inf.readEoln();

    set<pair<int, int>> connections;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, m, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        // CHECK: k is described as the number of possible connections, so each listed pair is distinct.
        ensuref(connections.insert({x, y}).second,
                "duplicate connection at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
