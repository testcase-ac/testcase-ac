#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2 * n, "m");
    inf.readEoln();

    vector<bool> seen(2 * n + 1, false);
    for (int i = 0; i < m; ++i) {
        string robot = inf.readToken("A|B", "robot");
        inf.readSpace();
        string action = inf.readToken("BLOCK", "action");
        inf.readSpace();
        int block = inf.readInt(1, 2 * n, "block");
        inf.readEoln();

        ensuref(i != 0 || robot == "A", "first record must be by robot A");
        ensuref(!seen[block], "duplicate block number at record %d: %d", i + 1, block);
        seen[block] = true;
        (void)action;
    }

    inf.readEof();
}
