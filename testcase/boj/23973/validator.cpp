#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2500, "M");
    inf.readEoln();

    int hitCount = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[01]{1,2500}", "row");
        ensuref((int)row.size() == m, "row %d has length %d, expected %d", i + 1,
                (int)row.size(), m);
        for (char cell : row) {
            if (cell == '1') {
                ++hitCount;
            }
        }
        inf.readEoln();
    }

    ensuref(hitCount <= 100000, "hit count is %d, expected at most 100000",
            hitCount);

    inf.readEof();
}
