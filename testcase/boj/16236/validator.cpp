#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "N");
    inf.readEoln();

    int sharkCount = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int cell = inf.readInt(0, 9, "cell");
            ensuref(cell <= 6 || cell == 9,
                    "invalid cell value at row %d column %d: %d",
                    r + 1, c + 1, cell);
            if (cell == 9) {
                ++sharkCount;
            }

            if (c + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    ensuref(sharkCount == 1, "expected exactly one baby shark, found %d", sharkCount);
    inf.readEof();
}
