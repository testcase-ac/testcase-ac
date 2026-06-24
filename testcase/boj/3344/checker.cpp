#include "testlib.h"

#include <vector>

using namespace std;

struct Placement {
    vector<int> colByRow;
};

int n;

Placement readPlacement(InStream& stream) {
    Placement placement;
    placement.colByRow.resize(n + 1);

    vector<char> usedCol(n + 1, 0);
    vector<char> usedDiagDown(2 * n + 1, 0);
    vector<char> usedDiagUp(2 * n + 1, 0);

    for (int row = 1; row <= n; ++row) {
        int col = stream.readInt(1, n, format("column[%d]", row).c_str());
        stream.readEoln();

        int diagDown = row - col + n;
        int diagUp = row + col;

        if (usedCol[col]) {
            stream.quitf(_wa, "column %d is used by more than one queen", col);
        }
        if (usedDiagDown[diagDown]) {
            stream.quitf(_wa, "two queens share diagonal row-column=%d", row - col);
        }
        if (usedDiagUp[diagUp]) {
            stream.quitf(_wa, "two queens share diagonal row+column=%d", row + col);
        }

        usedCol[col] = 1;
        usedDiagDown[diagDown] = 1;
        usedDiagUp[diagUp] = 1;
        placement.colByRow[row] = col;
    }

    stream.readEof();
    return placement;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();

    readPlacement(ans);
    readPlacement(ouf);

    quitf(_ok, "valid N-Queen placement for N=%d", n);
}
