#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    int k = inf.readInt(0, 50, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        // CHECK: M has no written bound; cap by the 20 possible natural heights
        // and treat hole heights as positions on a tree, so they must be distinct.
        int m = inf.readInt(1, 20, "m");
        vector<bool> seen(21, false);
        for (int j = 1; j <= m; ++j) {
            inf.readSpace();
            int h = inf.readInt(1, 20, "h");
            ensuref(!seen[h], "duplicate hole height %d on tree %d", h, i);
            seen[h] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}
