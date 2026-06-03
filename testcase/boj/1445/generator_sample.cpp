#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

bool inside(int r, int c, int n, int m) {
    return 0 <= r && r < n && 0 <= c && c < m;
}

vector<pair<int, int>> borderCells(int n, int m) {
    vector<pair<int, int>> cells;
    for (int r = 0; r < n; ++r) {
        cells.push_back({r, 0});
        cells.push_back({r, m - 1});
    }
    for (int c = 1; c + 1 < m; ++c) {
        cells.push_back({0, c});
        cells.push_back({n - 1, c});
    }
    return cells;
}

void putRandomGarbage(vector<string>& grid, int n, int m, int count) {
    vector<pair<int, int>> cells;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] == '.') {
                cells.push_back({r, c});
            }
        }
    }
    shuffle(cells.begin(), cells.end());
    count = min(count, (int)cells.size());
    for (int i = 0; i < count; ++i) {
        grid[cells[i].first][cells[i].second] = 'g';
    }
}

void putCluster(vector<string>& grid, int n, int m, int centerR, int centerC, int radius,
                int attempts) {
    for (int i = 0; i < attempts; ++i) {
        int r = centerR + rnd.next(-radius, radius);
        int c = centerC + rnd.next(-radius, radius);
        if (inside(r, c, n, m) && grid[r][c] == '.' &&
            abs(r - centerR) + abs(c - centerC) <= radius) {
            grid[r][c] = 'g';
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    if (mode == 6) {
        n = rnd.next(35, 50);
        m = rnd.next(35, 50);
    } else if (rnd.next(0, 4) == 0) {
        n = rnd.next(3, 5);
        m = rnd.next(3, 6);
    } else {
        n = rnd.next(6, 15);
        m = rnd.next(6, 15);
    }

    vector<string> grid(n, string(m, '.'));

    vector<pair<int, int>> starts = borderCells(n, m);
    pair<int, int> start = rnd.any(starts);
    pair<int, int> flower = {rnd.next(1, n - 2), rnd.next(1, m - 2)};
    grid[start.first][start.second] = 'S';
    grid[flower.first][flower.second] = 'F';

    if (mode == 0) {
        putRandomGarbage(grid, n, m, rnd.next(0, max(1, n * m / 9)));
    } else if (mode == 1) {
        int row = rnd.next(1, n - 2);
        int gap = rnd.next(0, m - 1);
        for (int c = 0; c < m; ++c) {
            if (c != gap && grid[row][c] == '.') {
                grid[row][c] = 'g';
            }
        }
        putRandomGarbage(grid, n, m, rnd.next(0, max(1, n * m / 14)));
    } else if (mode == 2) {
        int col = rnd.next(1, m - 2);
        int gap = rnd.next(0, n - 1);
        for (int r = 0; r < n; ++r) {
            if (r != gap && grid[r][col] == '.') {
                grid[r][col] = 'g';
            }
        }
        putRandomGarbage(grid, n, m, rnd.next(0, max(1, n * m / 14)));
    } else if (mode == 3) {
        int radius = rnd.next(1, min(4, max(n, m)));
        putCluster(grid, n, m, flower.first, flower.second, radius, rnd.next(4, 18));
        putRandomGarbage(grid, n, m, rnd.next(0, max(1, n * m / 18)));
    } else if (mode == 4) {
        int clusters = rnd.next(2, 5);
        for (int i = 0; i < clusters; ++i) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            putCluster(grid, n, m, r, c, rnd.next(1, 3), rnd.next(3, 12));
        }
    } else if (mode == 5) {
        for (int r = 0; r < n; ++r) {
            for (int c = (r + rnd.next(0, 1)) % 2; c < m; c += 2) {
                if (grid[r][c] == '.' && rnd.next(0, 99) < rnd.next(25, 55)) {
                    grid[r][c] = 'g';
                }
            }
        }
    } else {
        putRandomGarbage(grid, n, m, rnd.next(n * m / 8, n * m / 3));
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
