#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

static vector<pair<int, int>> allCells(int m, int n) {
    vector<pair<int, int>> cells;
    for (int r = 1; r <= m; ++r) {
        for (int c = 1; c <= n; ++c) {
            cells.push_back({r, c});
        }
    }
    return cells;
}

static int randomUnreachableValue(int m, int n) {
    vector<int> candidates;
    for (int x = 1; x <= 1000000; ++x) {
        bool reachable = false;
        for (int r = 1; r <= m && !reachable; ++r) {
            if (x % r == 0) {
                int c = x / r;
                reachable = 1 <= c && c <= n;
            }
        }
        if (!reachable) {
            candidates.push_back(x);
            if (candidates.size() >= 200) {
                break;
            }
        }
    }
    return rnd.any(candidates);
}

static void printGrid(const vector<vector<int>>& grid) {
    int m = int(grid.size()) - 1;
    int n = int(grid[1].size()) - 1;
    println(m);
    println(n);
    for (int r = 1; r <= m; ++r) {
        vector<int> row;
        for (int c = 1; c <= n; ++c) {
            row.push_back(grid[r][c]);
        }
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int m = 1;
    int n = 1;

    if (mode == 0) {
        m = 1;
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        m = rnd.next(2, 9);
        n = rnd.next(2, 9);
    } else {
        m = rnd.next(2, 12);
        n = rnd.next(2, 12);
    }

    vector<vector<int>> grid(m + 1, vector<int>(n + 1, 1));
    auto cells = allCells(m, n);

    if (mode == 0) {
        for (int c = 1; c <= n; ++c) {
            grid[1][c] = rnd.next(1, n);
        }
        if (rnd.next(2) == 0) {
            grid[1][1] = n;
        }
    } else if (mode == 1) {
        int dead = randomUnreachableValue(m, n);
        for (int r = 1; r <= m; ++r) {
            for (int c = 1; c <= n; ++c) {
                grid[r][c] = rnd.next(1, min(1000000, m * n + 20));
            }
        }
        grid[1][1] = dead;
    } else if (mode == 2) {
        for (int r = 1; r <= m; ++r) {
            for (int c = 1; c <= n; ++c) {
                auto target = rnd.any(cells);
                grid[r][c] = target.first * target.second;
            }
        }
    } else {
        shuffle(cells.begin(), cells.end());
        vector<pair<int, int>> path;
        path.push_back({1, 1});
        int extra = rnd.next(0, min(5, int(cells.size()) - 2));
        for (auto cell : cells) {
            if (cell != make_pair(1, 1) && cell != make_pair(m, n)) {
                if (extra == 0) {
                    break;
                }
                path.push_back(cell);
                --extra;
            }
        }
        path.push_back({m, n});

        for (int r = 1; r <= m; ++r) {
            for (int c = 1; c <= n; ++c) {
                auto target = rnd.any(cells);
                grid[r][c] = target.first * target.second;
            }
        }
        for (int i = 0; i + 1 < int(path.size()); ++i) {
            grid[path[i].first][path[i].second] = path[i + 1].first * path[i + 1].second;
        }
    }

    printGrid(grid);
    return 0;
}
