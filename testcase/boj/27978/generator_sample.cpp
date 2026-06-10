#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

static void placeEndpoints(vector<string>& grid, Cell ship, Cell treasure) {
    grid[ship.first][ship.second] = 'K';
    grid[treasure.first][treasure.second] = '*';
}

static Cell randomOpenCell(const vector<string>& grid) {
    vector<Cell> cells;
    for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
        for (int c = 0; c < static_cast<int>(grid[r].size()); ++c) {
            if (grid[r][c] == '.') {
                cells.push_back({r, c});
            }
        }
    }
    return rnd.any(cells);
}

static Cell differentOpenCell(const vector<string>& grid, Cell first) {
    Cell second = randomOpenCell(grid);
    while (second == first) {
        second = randomOpenCell(grid);
    }
    return second;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h = rnd.next(3, 12);
    int w = rnd.next(3, 16);
    vector<string> grid(h, string(w, '.'));
    Cell ship;
    Cell treasure;

    if (mode == 0) {
        ship = {rnd.next(0, h - 1), rnd.next(0, max(0, w / 3))};
        treasure = {rnd.next(0, h - 1), rnd.next(max(0, w * 2 / 3), w - 1)};
        if (ship == treasure) {
            treasure = {(ship.first + 1) % h, treasure.second};
        }
    } else if (mode == 1) {
        ship = {rnd.next(0, h - 1), rnd.next(max(0, w * 2 / 3), w - 1)};
        treasure = {rnd.next(0, h - 1), rnd.next(0, max(0, w / 3))};
        if (ship == treasure) {
            treasure = {(ship.first + 1) % h, treasure.second};
        }
    } else if (mode == 2) {
        int gap = rnd.next(0, h - 1);
        int wallCol = rnd.next(1, w - 2);
        for (int r = 0; r < h; ++r) {
            if (r != gap) {
                grid[r][wallCol] = '#';
            }
        }
        for (int r = max(0, gap - 1); r <= min(h - 1, gap + 1); ++r) {
            grid[r][wallCol] = '.';
        }
        ship = {rnd.next(0, h - 1), rnd.next(0, wallCol - 1)};
        treasure = {rnd.next(0, h - 1), rnd.next(wallCol + 1, w - 1)};
    } else if (mode == 3) {
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if (rnd.next(0, 99) < 35) {
                    grid[r][c] = '#';
                }
            }
        }
        int r = rnd.next(0, h - 1);
        for (int c = 0; c < w; ++c) {
            grid[r][c] = '.';
            if (r + 1 < h && rnd.next(0, 99) < 45) {
                ++r;
                grid[r][c] = '.';
            } else if (r > 0 && rnd.next(0, 99) < 45) {
                --r;
                grid[r][c] = '.';
            }
        }
        ship = randomOpenCell(grid);
        treasure = differentOpenCell(grid, ship);
    } else if (mode == 4) {
        int wallRow = rnd.next(1, h - 2);
        for (int c = 0; c < w; ++c) {
            grid[wallRow][c] = '#';
        }
        if (rnd.next(0, 1) == 0) {
            ship = {rnd.next(0, wallRow - 1), rnd.next(0, w - 1)};
            treasure = {rnd.next(wallRow + 1, h - 1), rnd.next(0, w - 1)};
        } else {
            ship = {rnd.next(wallRow + 1, h - 1), rnd.next(0, w - 1)};
            treasure = {rnd.next(0, wallRow - 1), rnd.next(0, w - 1)};
        }
    } else {
        int reefChance = rnd.next(5, 45);
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if (rnd.next(0, 99) < reefChance) {
                    grid[r][c] = '#';
                }
            }
        }
        Cell first = {rnd.next(0, h - 1), rnd.next(0, w - 1)};
        Cell second = {rnd.next(0, h - 1), rnd.next(0, w - 1)};
        while (second == first) {
            second = {rnd.next(0, h - 1), rnd.next(0, w - 1)};
        }
        grid[first.first][first.second] = '.';
        grid[second.first][second.second] = '.';
        ship = randomOpenCell(grid);
        treasure = differentOpenCell(grid, ship);
    }

    placeEndpoints(grid, ship, treasure);

    println(h, w);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
