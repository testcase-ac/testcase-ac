#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<string> makeGrid(int n, int m, char fill) {
    return vector<string>(n, string(m, fill));
}

void setDots(vector<string>& grid, int targetDots) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < (int)grid.size(); ++i) {
        for (int j = 0; j < (int)grid[i].size(); ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());
    targetDots = min(targetDots, (int)cells.size());
    for (int i = 0; i < targetDots; ++i) {
        grid[cells[i].first][cells[i].second] = '.';
    }
}

vector<string> makeCase(int mode) {
    if (mode == 0) {
        int n = rnd.next(1, 2);
        int m = rnd.next(1, 3);
        auto grid = makeGrid(n, m, 'x');
        setDots(grid, rnd.next(0, n * m));
        return grid;
    }

    if (mode == 1) {
        int n = rnd.next(3, 8);
        int m = rnd.next(3, 8);
        auto grid = makeGrid(n, m, 'x');
        int dots = rnd.next(0, n * m);
        int wantedParity = rnd.next(2);
        if (dots % 2 != wantedParity) {
            dots = dots == n * m ? dots - 1 : dots + 1;
        }
        setDots(grid, dots);
        return grid;
    }

    if (mode == 2) {
        int n = rnd.next(3, 9);
        int m = rnd.next(3, 9);
        auto grid = makeGrid(n, m, 'x');
        int top = rnd.next(0, n - 3);
        int left = rnd.next(0, m - 3);
        for (int i = top; i < top + 3; ++i) {
            for (int j = left; j < left + 3; ++j) {
                grid[i][j] = '.';
            }
        }
        int extra = rnd.next(0, min(8, n * m - 9));
        while (extra > 0) {
            int r = rnd.next(n);
            int c = rnd.next(m);
            if (grid[r][c] == 'x') {
                grid[r][c] = '.';
                --extra;
            }
        }
        return grid;
    }

    if (mode == 3) {
        int n = rnd.next(4, 10);
        int m = rnd.next(4, 10);
        auto grid = makeGrid(n, m, 'x');
        int pattern = rnd.next(3);
        int phase = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool open = false;
                if (pattern == 0) {
                    open = (i % 2 == phase);
                } else if (pattern == 1) {
                    open = (j % 2 == phase);
                } else {
                    open = ((i + j) % 2 == phase);
                }
                grid[i][j] = open ? '.' : 'x';
            }
        }
        return grid;
    }

    if (mode == 4) {
        int n = rnd.next(3, 12);
        int m = rnd.next(3, 12);
        auto grid = makeGrid(n, m, '.');
        int holes = rnd.next(0, min(n * m, 30));
        while (holes > 0) {
            int r = rnd.next(n);
            int c = rnd.next(m);
            if (grid[r][c] == '.') {
                grid[r][c] = 'x';
                --holes;
            }
        }
        return grid;
    }

    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    auto grid = makeGrid(n, m, 'x');
    int dotProbability = rnd.next(10, 90);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (rnd.next(100) < dotProbability) {
                grid[i][j] = '.';
            }
        }
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    vector<vector<string>> cases;
    int totalArea = 0;
    for (int tc = 0; tc < t; ++tc) {
        vector<string> grid;
        do {
            grid = makeCase(rnd.next(6));
        } while (totalArea + (int)grid.size() * (int)grid[0].size() > 10000);
        totalArea += (int)grid.size() * (int)grid[0].size();
        cases.push_back(grid);
    }

    println((int)cases.size());
    for (const auto& grid : cases) {
        println((int)grid.size(), (int)grid[0].size());
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
