#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readEoln();

    int startCount = 0;
    int destinationCount = 0;

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[0-3]{1,500}", "row");
        inf.readEoln();

        ensuref((int)row.size() == m,
                "row %d length is %d, expected %d",
                i + 1,
                (int)row.size(),
                m);

        for (char cell : row) {
            if (cell == '2') {
                ++startCount;
            } else if (cell == '3') {
                ++destinationCount;
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one start cell, found %d", startCount);
    ensuref(destinationCount == 1,
            "expected exactly one destination cell, found %d",
            destinationCount);

    inf.readEof();
    return 0;
}
