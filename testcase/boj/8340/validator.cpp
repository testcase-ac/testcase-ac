#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    vector<vector<int>> grid(2, vector<int>(n));
    vector<int> frequency(n + 1, 0);

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < n; ++col) {
            if (col > 0) {
                inf.readSpace();
            }
            int value = inf.readInt(1, n, "cell");
            grid[row][col] = value;
            ++frequency[value];
        }
        inf.readEoln();
    }

    for (int col = 0; col < n; ++col) {
        ensuref(grid[0][col] != grid[1][col],
                "column %d contains the same number twice: %d",
                col + 1, grid[0][col]);
    }

    for (int value = 1; value <= n; ++value) {
        ensuref(frequency[value] == 2,
                "number %d appears %d times instead of twice",
                value, frequency[value]);
    }

    inf.readEof();
}
