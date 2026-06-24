#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int grid[10][10];

struct Answer {
    int value;
    int row;
    int col;
};

Answer readAnswer(InStream& stream, int maxValue) {
    int value = stream.readInt(0, 99, "maximum value");
    stream.readEoln();

    int row = stream.readInt(1, 9, "row");
    stream.readSpace();
    int col = stream.readInt(1, 9, "column");
    stream.readEoln();
    stream.readEof();

    if (value != maxValue) {
        stream.quitf(_wa, "reported maximum is %d, expected %d", value, maxValue);
    }
    if (grid[row][col] != maxValue) {
        stream.quitf(_wa, "cell (%d, %d) contains %d, expected maximum %d",
                     row, col, grid[row][col], maxValue);
    }

    return {value, row, col};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int maxValue = 0;
    for (int row = 1; row <= 9; ++row) {
        for (int col = 1; col <= 9; ++col) {
            grid[row][col] = inf.readInt();
            maxValue = max(maxValue, grid[row][col]);
        }
    }

    readAnswer(ans, maxValue);
    Answer participant = readAnswer(ouf, maxValue);

    quitf(_ok, "maximum %d at (%d, %d)", participant.value, participant.row, participant.col);
}
