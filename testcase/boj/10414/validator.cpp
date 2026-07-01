#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readSpace();
    int p = inf.readInt(0, n, "p");
    inf.readEoln();

    vector<bool> seenInsecure(n + 1, false);
    for (int i = 0; i < p; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int building = inf.readInt(1, n, "insecure_i");
        ensuref(!seenInsecure[building], "duplicate insecure building: %d", building);
        seenInsecure[building] = true;
    }
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readSpace();
        int length = inf.readInt(1, 10000, "l_i");
        (void)length;
        inf.readEoln();

        ensuref(x != y, "self-loop at edge %d: %d", i + 1, x);
        auto edge = minmax(x, y);
        ensuref(edges.insert(edge).second, "duplicate direct link at edge %d: %d %d",
                i + 1, x, y);
    }

    inf.readEof();
}
