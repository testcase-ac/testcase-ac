#include "testlib.h"

#include <string>

using namespace std;

bool isAllowedTile(int value) {
    if (value == 0) {
        return true;
    }
    if (value < 2 || value > 1024) {
        return false;
    }
    return (value & (value - 1)) == 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        // CHECK: The statement is for the Small dataset and gives N <= 4, even
        // though its non-graded sample includes a larger illustrative board.
        int n = inf.readInt(1, 4, "N");
        inf.readSpace();
        string dir = inf.readToken("left|right|up|down", "DIR");
        inf.readEoln();

        for (int row = 1; row <= n; ++row) {
            for (int col = 1; col <= n; ++col) {
                int value = inf.readInt(0, 1024, "tile");
                ensuref(isAllowedTile(value),
                        "tile at case %d row %d col %d is not 0 or a power of two in [2, 1024]: %d",
                        tc, row, col, value);
                if (col < n) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
}
