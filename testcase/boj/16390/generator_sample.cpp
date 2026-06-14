#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using Cell = pair<int, int>;

vector<Cell> triangleShape() {
    return {{0, 0}, {0, 1}, {1, 0}};
}

vector<Cell> diamondShape(int radius) {
    vector<Cell> cells;
    int center = radius;
    for (int r = 0; r <= 2 * radius; ++r) {
        for (int c = 0; c <= 2 * radius; ++c) {
            if (abs(r - center) + abs(c - center) == radius) {
                cells.emplace_back(r, c);
            }
        }
    }
    return cells;
}

int heightOf(const vector<Cell>& shape) {
    int h = 0;
    for (auto [r, c] : shape) {
        h = max(h, r + 1);
    }
    return h;
}

int widthOf(const vector<Cell>& shape) {
    int w = 0;
    for (auto [r, c] : shape) {
        w = max(w, c + 1);
    }
    return w;
}

bool canPlace(const vector<string>& grid, const vector<Cell>& shape, int top,
              int left) {
    int m = (int)grid.size();
    int n = (int)grid[0].size();
    set<Cell> own;
    for (auto [r, c] : shape) {
        int nr = top + r;
        int nc = left + c;
        if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
            return false;
        }
        own.insert({nr, nc});
    }

    for (auto [r, c] : own) {
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                int nr = r + dr;
                int nc = c + dc;
                if (0 <= nr && nr < m && 0 <= nc && nc < n &&
                    grid[nr][nc] == '#' && !own.count({nr, nc})) {
                    return false;
                }
            }
        }
    }
    return true;
}

void place(vector<string>& grid, const vector<Cell>& shape, int top, int left) {
    for (auto [r, c] : shape) {
        grid[top + r][left + c] = '#';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int m = rnd.next(1, 30);
    int n = rnd.next(1, 30);
    vector<string> grid(m, string(n, '.'));

    vector<vector<Cell>> shapes = {triangleShape(), diamondShape(2),
                                   diamondShape(3), diamondShape(4)};
    shuffle(shapes.begin(), shapes.end());

    int targetLoops = rnd.next(0, 8);
    for (int loop = 0; loop < targetLoops; ++loop) {
        vector<Cell> shape = rnd.any(shapes);
        if (heightOf(shape) > m || widthOf(shape) > n) {
            continue;
        }

        vector<Cell> positions;
        for (int r = 0; r + heightOf(shape) <= m; ++r) {
            for (int c = 0; c + widthOf(shape) <= n; ++c) {
                if (canPlace(grid, shape, r, c)) {
                    positions.emplace_back(r, c);
                }
            }
        }
        if (positions.empty()) {
            continue;
        }

        auto [top, left] = rnd.any(positions);
        place(grid, shape, top, left);
    }

    println(m, n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
