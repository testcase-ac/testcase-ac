#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int dr[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dc[8] = {2, 1, -1, -2, -2, -1, 1, 2};

bool inside(int r, int c, int rows, int cols) {
    return 0 <= r && r < rows && 0 <= c && c < cols;
}

vector<pair<int, int>> knightNeighbors(int r, int c, int rows, int cols) {
    vector<pair<int, int>> result;
    for (int k = 0; k < 8; ++k) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if (inside(nr, nc, rows, cols)) {
            result.push_back({nr, nc});
        }
    }
    return result;
}

void printGrid(vector<vector<int>> grid, pair<int, int> start, pair<int, int> target) {
    grid[start.first][start.second] = 3;
    grid[target.first][target.second] = 4;

    println(static_cast<int>(grid.size()), static_cast<int>(grid[0].size()));
    for (const auto& row : grid) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int rows = 1;
    int cols = 1;

    if (mode == 0) {
        rows = rnd.next(1, 3);
        cols = rnd.next(2, 4);
    } else if (mode == 1) {
        rows = rnd.next(3, 6);
        cols = rnd.next(3, 6);
    } else if (mode == 2) {
        rows = rnd.next(4, 8);
        cols = rnd.next(4, 8);
    } else if (mode == 3) {
        rows = rnd.next(5, 10);
        cols = rnd.next(5, 10);
    } else {
        rows = rnd.next(8, 15);
        cols = rnd.next(8, 15);
    }

    vector<pair<int, int>> cells;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> start = cells[0];
    pair<int, int> target = cells[1];
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    if (mode == 1) {
        vector<pair<int, int>> choices;
        for (auto cell : cells) {
            if (!knightNeighbors(cell.first, cell.second, rows, cols).empty()) {
                choices.push_back(cell);
            }
        }
        start = rnd.any(choices);
        auto neighbors = knightNeighbors(start.first, start.second, rows, cols);
        target = rnd.any(neighbors);
    } else if (mode == 3) {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                grid[r][c] = rnd.next(100) < 65 ? 2 : 0;
            }
        }
    } else {
        int lilyPercent = mode == 4 ? rnd.next(15, 45) : rnd.next(5, 30);
        int rockPercent = mode == 4 ? rnd.next(10, 35) : rnd.next(0, 25);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int roll = rnd.next(100);
                if (roll < rockPercent) {
                    grid[r][c] = 2;
                } else if (roll < rockPercent + lilyPercent) {
                    grid[r][c] = 1;
                }
            }
        }
    }

    if (mode == 2 || mode == 4) {
        int pathLen = rnd.next(2, min(6, static_cast<int>(cells.size()) - 1));
        pair<int, int> cur = start;
        grid[cur.first][cur.second] = 1;
        for (int step = 0; step < pathLen; ++step) {
            auto nextCells = knightNeighbors(cur.first, cur.second, rows, cols);
            if (nextCells.empty()) {
                break;
            }
            cur = rnd.any(nextCells);
            if (cur == start) {
                continue;
            }
            grid[cur.first][cur.second] = rnd.next(100) < 55 ? 1 : 0;
            target = cur;
        }
    }

    grid[start.first][start.second] = 0;
    grid[target.first][target.second] = 0;
    printGrid(grid, start, target);
    return 0;
}
