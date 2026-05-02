#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H and W
    int H = inf.readInt(1, 20, "H");
    inf.readSpace();
    int W = inf.readInt(1, 20, "W");
    inf.readEoln();

    // Read the board
    for (int i = 0; i < H; ++i) {
        string row = inf.readLine("[.X]{"+to_string(W)+","+to_string(W)+"}", "board row");
        ensuref((int)row.size() == W, "Row %d length is %d, expected %d", i+1, (int)row.size(), W);
        for (int j = 0; j < W; ++j) {
            ensuref(row[j] == '.' || row[j] == 'X', "Invalid character '%c' at row %d, col %d", row[j], i+1, j+1);
        }
    }

    inf.readEof();
}
