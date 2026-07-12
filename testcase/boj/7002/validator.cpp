#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = inf.readInt(1, 14, "tc");
    inf.readEoln();

    for (int caseNo = 1; caseNo <= tc; ++caseNo) {
        setTestCase(caseNo);

        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1000, "m");
        inf.readSpace();
        int t = inf.readInt(1, 1000000, "t");
        inf.readSpace();
        int r = inf.readInt(1, 100000000, "r");
        inf.readEoln();

        (void)t;
        (void)r;

        for (int row = 1; row <= n; ++row) {
            string line = inf.readLine("[^]{1,1000}", "map_row");
            ensuref((int)line.size() == m,
                    "row %d has length %d, expected %d", row, (int)line.size(), m);
            for (int col = 1; col <= m; ++col) {
                char cell = line[col - 1];
                ensuref(cell == '*' || cell == 'O' || cell == 'X',
                        "invalid map character at row %d, column %d: %c", row, col, cell);
            }
        }
    }

    inf.readEof();
}
