#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    inf.readInt(0, 500, "t");
    inf.readSpace();
    inf.readInt(1, n, "r");
    inf.readSpace();
    inf.readInt(1, n, "c");
    inf.readEoln();

    string rowPattern = "[#\\.]{1,500}";
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken(rowPattern, "grid_row");
        ensuref((int)row.size() == n, "grid row %d has length %d, expected %d",
                i + 1, (int)row.size(), n);
        inf.readEoln();
    }

    inf.readEof();
}
