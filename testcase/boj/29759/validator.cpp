#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

void ensureCoprimePairwise(const vector<int>& values, const char* groupName, int groupIndex) {
    for (int i = 0; i < int(values.size()); ++i) {
        if (values[i] == 0) continue;
        for (int j = i + 1; j < int(values.size()); ++j) {
            if (values[j] == 0) continue;
            ensuref(gcd(values[i], values[j]) == 1,
                    "%s %d has non-coprime values %d and %d",
                    groupName,
                    groupIndex,
                    values[i],
                    values[j]);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10, "N");
    inf.readEoln();

    int size = n * n;
    vector<vector<int>> board(size, vector<int>(size));
    bool hasEmptyCell = false;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (j > 0) inf.readSpace();
            board[i][j] = inf.readInt(0, 1000000, "a_ij");
            ensuref(board[i][j] != 1, "a_%d_%d must not be 1", i + 1, j + 1);
            hasEmptyCell = hasEmptyCell || board[i][j] == 0;
        }
        inf.readEoln();
    }

    ensuref(hasEmptyCell, "board must contain at least one empty cell");

    for (int i = 0; i < size; ++i) {
        ensureCoprimePairwise(board[i], "row", i + 1);
    }

    for (int j = 0; j < size; ++j) {
        vector<int> column;
        column.reserve(size);
        for (int i = 0; i < size; ++i) {
            column.push_back(board[i][j]);
        }
        ensureCoprimePairwise(column, "column", j + 1);
    }

    for (int blockRow = 0; blockRow < n; ++blockRow) {
        for (int blockCol = 0; blockCol < n; ++blockCol) {
            vector<int> block;
            block.reserve(size);
            for (int i = blockRow * n; i < (blockRow + 1) * n; ++i) {
                for (int j = blockCol * n; j < (blockCol + 1) * n; ++j) {
                    block.push_back(board[i][j]);
                }
            }
            ensureCoprimePairwise(block, "block", blockRow * n + blockCol + 1);
        }
    }

    inf.readEof();
}
