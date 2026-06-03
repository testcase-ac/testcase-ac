#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

vector<Cell> makeShape(int targetSize) {
    vector<Cell> cells = {{0, 0}};

    while ((int)cells.size() < targetSize) {
        Cell base = rnd.any(cells);
        int dir = rnd.next(4);
        Cell next = base;
        if (dir == 0) --next.first;
        if (dir == 1) ++next.first;
        if (dir == 2) --next.second;
        if (dir == 3) ++next.second;

        if (find(cells.begin(), cells.end(), next) == cells.end()) {
            cells.push_back(next);
        }
    }

    int minR = cells[0].first;
    int minC = cells[0].second;
    for (Cell cell : cells) {
        minR = min(minR, cell.first);
        minC = min(minC, cell.second);
    }
    for (Cell& cell : cells) {
        cell.first -= minR;
        cell.second -= minC;
    }

    return cells;
}

bool canPlace(const vector<string>& grid, const vector<Cell>& shape, int baseR, int baseC) {
    int n = grid.size();
    int m = grid[0].size();
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (Cell cell : shape) {
        int r = baseR + cell.first;
        int c = baseC + cell.second;
        if (r < 0 || r >= n || c < 0 || c >= m || grid[r][c] == 'X') {
            return false;
        }
    }

    for (Cell cell : shape) {
        int r = baseR + cell.first;
        int c = baseC + cell.second;
        for (int dir = 0; dir < 4; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (0 <= nr && nr < n && 0 <= nc && nc < m && grid[nr][nc] == 'X') {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 12);
    int m = rnd.next(3, 16);
    vector<string> grid(n, string(m, '.'));

    for (int spot = 0; spot < 3; ++spot) {
        bool placed = false;
        for (int attempt = 0; attempt < 1000 && !placed; ++attempt) {
            int size = rnd.next(1, 8);
            if (rnd.next(5) == 0) {
                size = rnd.next(1, 3);
            }

            vector<Cell> shape = makeShape(size);
            int height = 0;
            int width = 0;
            for (Cell cell : shape) {
                height = max(height, cell.first + 1);
                width = max(width, cell.second + 1);
            }
            if (height > n || width > m) {
                continue;
            }

            int baseR = rnd.next(0, n - height);
            int baseC = rnd.next(0, m - width);
            if (!canPlace(grid, shape, baseR, baseC)) {
                continue;
            }

            for (Cell cell : shape) {
                grid[baseR + cell.first][baseC + cell.second] = 'X';
            }
            placed = true;
        }

        if (!placed) {
            n = 3;
            m = 5;
            grid = {"X.X.X", ".....", "....."};
            break;
        }
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
