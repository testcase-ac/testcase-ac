#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {1, 0, -1, 0};

bool seesEntrance(const vector<string>& grid, int x, int y, int dir, int sx, int sy) {
    int nx = x + DX[dir];
    int ny = y + DY[dir];
    int n = grid.size();
    int m = grid[0].size();

    while (0 <= nx && nx < n && 0 <= ny && ny < m) {
        char cell = grid[nx][ny];
        if (cell == '#' || ('0' <= cell && cell <= '3')) {
            break;
        }
        if (nx == sx && ny == sy) {
            return true;
        }
        nx += DX[dir];
        ny += DY[dir];
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, mode == 4 ? 18 : 12);
    int m = rnd.next(2, mode == 4 ? 18 : 12);

    vector<string> grid(n, string(m, '.'));
    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> start = cells[0];
    pair<int, int> finish = cells[1];

    int wallPercent = 0;
    int ghostPercent = 0;
    if (mode == 0) {
        wallPercent = rnd.next(0, 12);
        ghostPercent = rnd.next(0, 8);
    } else if (mode == 1) {
        wallPercent = rnd.next(25, 48);
        ghostPercent = rnd.next(0, 10);
    } else if (mode == 2) {
        wallPercent = rnd.next(12, 28);
        ghostPercent = rnd.next(12, 28);
    } else if (mode == 3) {
        wallPercent = rnd.next(8, 25);
        ghostPercent = rnd.next(28, 55);
    } else {
        wallPercent = rnd.next(15, 35);
        ghostPercent = rnd.next(8, 22);
    }

    for (auto [x, y] : cells) {
        if (make_pair(x, y) == start || make_pair(x, y) == finish) {
            continue;
        }
        bool corridorGap = mode == 2 && (x == start.first || y == finish.second);
        if (!corridorGap && rnd.next(0, 99) < wallPercent) {
            grid[x][y] = '#';
        }
    }

    shuffle(cells.begin(), cells.end());
    for (auto [x, y] : cells) {
        if (make_pair(x, y) == start || make_pair(x, y) == finish || grid[x][y] != '.') {
            continue;
        }
        if (rnd.next(0, 99) >= ghostPercent) {
            continue;
        }

        vector<int> dirs = {0, 1, 2, 3};
        shuffle(dirs.begin(), dirs.end());
        for (int dir : dirs) {
            if (!seesEntrance(grid, x, y, dir, start.first, start.second)) {
                grid[x][y] = char('0' + dir);
                break;
            }
        }
    }

    grid[start.first][start.second] = '.';
    grid[finish.first][finish.second] = '.';

    println(n, m);
    println(start.first + 1, start.second + 1, finish.first + 1, finish.second + 1);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
