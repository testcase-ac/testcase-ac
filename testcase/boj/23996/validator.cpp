#include "testlib.h"

#include <string>
using namespace std;

static bool isGoalState(const vector<string>& grid) {
    int n = int(grid.size());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool onMainDiagonal = (i == j);
            bool onAntiDiagonal = (i + j == n - 1);
            char expected = (onMainDiagonal || onAntiDiagonal) ? 'X' : '.';
            if (grid[i][j] != expected) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 55, "N");
        inf.readEoln();
        ensuref(n % 2 == 1, "N must be odd, got %d", n);

        vector<string> grid;
        int xCount = 0;
        for (int i = 0; i < n; ++i) {
            string row = inf.readLine("[X.]{1,55}", "row");
            ensuref(int(row.size()) == n,
                    "row %d must have length %d, got %d",
                    i + 1, n, int(row.size()));
            for (char cell : row) {
                xCount += (cell == 'X');
            }
            grid.push_back(row);
        }

        ensuref(xCount == 2 * n - 1,
                "grid must contain exactly %d X tiles, got %d",
                2 * n - 1, xCount);
        ensuref(!isGoalState(grid), "grid must not already be in the goal state");
    }

    inf.readEof();
}
