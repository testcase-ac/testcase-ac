#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static vector<string> emptyGrid(int n) {
    return vector<string>(n, string(n, '.'));
}

static void addRectangle(vector<string>& grid, int r1, int c1, int r2, int c2) {
    for (int r = r1; r <= r2; ++r) {
        for (int c = c1; c <= c2; ++c) {
            grid[r][c] = '#';
        }
    }
}

static vector<string> randomGrid(int n) {
    vector<string> grid = emptyGrid(n);
    int percent = rnd.next(10, 85);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (rnd.next(100) < percent) {
                grid[r][c] = '#';
            }
        }
    }
    return grid;
}

static vector<string> stripedGrid(int n) {
    vector<string> grid = emptyGrid(n);
    bool horizontal = rnd.next(2) == 0;
    int period = rnd.next(2, 4);
    int width = rnd.next(1, period);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int x = horizontal ? r : c;
            if (x % period < width) {
                grid[r][c] = '#';
            }
        }
    }
    return grid;
}

static vector<string> checkerGrid(int n) {
    vector<string> grid = emptyGrid(n);
    int parity = rnd.next(2);
    int noisePercent = rnd.next(0, 25);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if ((r + c) % 2 == parity) {
                grid[r][c] = '#';
            }
            if (rnd.next(100) < noisePercent) {
                grid[r][c] = grid[r][c] == '#' ? '.' : '#';
            }
        }
    }
    return grid;
}

static vector<string> blockGrid(int n) {
    vector<string> grid = emptyGrid(n);
    int blocks = rnd.next(1, min(6, n * n));
    for (int i = 0; i < blocks; ++i) {
        int r1 = rnd.next(n);
        int c1 = rnd.next(n);
        int r2 = rnd.next(r1, min(n - 1, r1 + rnd.next(0, 4)));
        int c2 = rnd.next(c1, min(n - 1, c1 + rnd.next(0, 4)));
        addRectangle(grid, r1, c1, r2, c2);
    }
    return grid;
}

static vector<string> pathGrid(int n) {
    vector<string> grid = emptyGrid(n);
    int r = rnd.next(n);
    int c = rnd.next(n);
    int steps = rnd.next(n, min(n * n, 3 * n));
    grid[r][c] = '#';
    for (int i = 0; i < steps; ++i) {
        vector<pair<int, int>> choices;
        if (r > 0) choices.push_back({r - 1, c});
        if (r + 1 < n) choices.push_back({r + 1, c});
        if (c > 0) choices.push_back({r, c - 1});
        if (c + 1 < n) choices.push_back({r, c + 1});
        pair<int, int> next = rnd.any(choices);
        r = next.first;
        c = next.second;
        grid[r][c] = '#';
    }
    return grid;
}

static vector<string> makeCase(int n, int mode) {
    if (mode == 0) {
        return emptyGrid(n);
    }
    if (mode == 1) {
        return vector<string>(n, string(n, '#'));
    }
    if (mode == 2) {
        return stripedGrid(n);
    }
    if (mode == 3) {
        return checkerGrid(n);
    }
    if (mode == 4) {
        return blockGrid(n);
    }
    if (mode == 5) {
        return pathGrid(n);
    }
    return randomGrid(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 8);
    println(cases);
    for (int tc = 0; tc < cases; ++tc) {
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 15);
        }

        int mode = (tc < 6) ? tc : rnd.next(0, 6);
        vector<string> grid = makeCase(n, mode);

        println(n);
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
