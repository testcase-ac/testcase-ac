#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10, "m");
    inf.readEoln();

    int pieceCount = 0;
    for (int row = 0; row < n; ++row) {
        string line = inf.readLine("[.1-9]{1,10}", "row");
        ensuref((int)line.size() == m, "row %d has length %d, expected %d", row + 1,
                (int)line.size(), m);
        for (char cell : line) {
            if (cell >= '1' && cell <= '9') {
                ++pieceCount;
            }
        }
    }

    ensuref(pieceCount >= 1, "board must contain at least one piece");
    inf.readEof();
}
