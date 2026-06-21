#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int k = inf.readInt(0, n * n, "k");
    inf.readEoln();

    int emptyCells = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[01]{1,100}", "row");
        inf.readEoln();

        ensuref((int)row.size() == n, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), n);
        for (char cell : row) {
            emptyCells += cell == '0';
        }
    }

    ensuref(emptyCells >= k, "board has %d empty cells, less than k=%d",
            emptyCells, k);

    inf.readEof();
}
