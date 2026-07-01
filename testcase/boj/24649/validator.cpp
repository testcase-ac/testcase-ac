#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const vector<pair<int, int>> kQ = {
    {0, 0}, {0, 1}, {0, 2},
    {1, 0},         {1, 2},
    {2, 0}, {2, 1}, {2, 2},
                    {3, 2},
                    {4, 2},
};

const vector<pair<int, int>> kF = {
    {0, 0}, {0, 1}, {0, 2},
    {1, 0},
    {2, 0}, {2, 1},
    {3, 0},
    {4, 0},
};

bool canErase(const vector<string>& grid, int top, int left,
              const vector<pair<int, int>>& shape) {
    int n = (int)grid.size();
    int m = (int)grid[0].size();
    for (auto [di, dj] : shape) {
        int row = top + di;
        int col = left + dj;
        if (row < 0 || row >= n || col < 0 || col >= m || grid[row][col] != '#') {
            return false;
        }
    }
    return true;
}

void eraseShape(vector<string>& grid, int top, int left,
                const vector<pair<int, int>>& shape) {
    for (auto [di, dj] : shape) {
        grid[top + di][left + dj] = '.';
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 300, "n");
    inf.readSpace();
    int m = inf.readInt(3, 300, "m");
    inf.readEoln();

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        grid[i] = inf.readToken("[.#]{3,300}", "grid_row");
        ensuref((int)grid[i].size() == m,
                "grid row %d has length %d, expected %d", i + 1, (int)grid[i].size(), m);
        inf.readEoln();
    }

    for (int col = m - 1; col >= 0; --col) {
        for (int row = 0; row < n; ++row) {
            if (grid[row][col] == '.') {
                continue;
            }

            int top = row;
            int left = col - 2;
            ensuref(left >= 0 && top + 4 < n,
                    "black cell at (%d, %d) cannot be the top-right of a letter",
                    row + 1, col + 1);

            if (canErase(grid, top, left, kQ)) {
                eraseShape(grid, top, left, kQ);
            } else if (canErase(grid, top, left, kF)) {
                eraseShape(grid, top, left, kF);
            } else {
                ensuref(false, "no Q or F letter can be erased at top-right (%d, %d)",
                        row + 1, col + 1);
            }
        }
    }

    inf.readEof();
}
