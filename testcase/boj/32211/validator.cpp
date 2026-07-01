#include "testlib.h"

#include <vector>

using namespace std;

static void ensurePermutation(const vector<int>& values, int maxValue, const char* label, int index) {
    vector<int> seen(maxValue + 1, 0);
    for (int value : values) {
        ensuref(!seen[value], "%s %d contains duplicate value %d", label, index, value);
        seen[value] = 1;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 40, "n");
    inf.readEoln();

    int side = n * n;
    vector<vector<int>> grid(side, vector<int>(side));

    for (int row = 0; row < side; ++row) {
        for (int col = 0; col < side; ++col) {
            if (col > 0) {
                inf.readSpace();
            }
            grid[row][col] = inf.readInt(1, side, "cell");
        }
        inf.readEoln();
        ensurePermutation(grid[row], side, "row", row + 1);
    }

    for (int col = 0; col < side; ++col) {
        vector<int> values;
        values.reserve(side);
        for (int row = 0; row < side; ++row) {
            values.push_back(grid[row][col]);
        }
        ensurePermutation(values, side, "column", col + 1);
    }

    for (int blockRow = 0; blockRow < n; ++blockRow) {
        for (int blockCol = 0; blockCol < n; ++blockCol) {
            vector<int> values;
            values.reserve(side);
            for (int row = blockRow * n; row < (blockRow + 1) * n; ++row) {
                for (int col = blockCol * n; col < (blockCol + 1) * n; ++col) {
                    values.push_back(grid[row][col]);
                }
            }
            ensurePermutation(values, side, "block", blockRow * n + blockCol + 1);
        }
    }

    inf.readEof();
}
