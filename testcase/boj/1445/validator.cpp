#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 50, "N");
    inf.readSpace();
    int m = inf.readInt(3, 50, "M");
    inf.readEoln();

    int startCount = 0;
    int flowerCount = 0;

    for (int r = 0; r < n; ++r) {
        string row = inf.readToken("[SFg.]{1,50}", "row");
        ensuref((int)row.size() == m, "row %d has length %d, expected %d", r + 1,
                (int)row.size(), m);
        inf.readEoln();

        for (int c = 0; c < m; ++c) {
            if (row[c] == 'S') {
                ++startCount;
                ensuref(r == 0 || r == n - 1 || c == 0 || c == m - 1,
                        "S must be on the border, found at row %d column %d",
                        r + 1, c + 1);
            } else if (row[c] == 'F') {
                ++flowerCount;
                ensuref(r != 0 && r != n - 1 && c != 0 && c != m - 1,
                        "F must not be on the border, found at row %d column %d",
                        r + 1, c + 1);
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one S, found %d", startCount);
    ensuref(flowerCount == 1, "expected exactly one F, found %d", flowerCount);

    inf.readEof();
}
