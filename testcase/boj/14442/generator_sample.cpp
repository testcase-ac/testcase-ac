#include "testlib.h"
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
using namespace std;

static void keepEndpointsOpen(vector<string>& grid) {
    grid[0][0] = '0';
    grid[(int)grid.size() - 1][(int)grid[0].size() - 1] = '0';
}

static vector<string> randomGrid(int n, int m) {
    int wallPercent = rnd.next(5, 75);
    vector<string> grid(n, string(m, '0'));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (rnd.next(100) < wallPercent) {
                grid[r][c] = '1';
            }
        }
    }
    keepEndpointsOpen(grid);
    return grid;
}

static vector<string> barrierGrid(int n, int m) {
    vector<string> grid(n, string(m, '0'));
    if (n >= m) {
        for (int r = 1; r + 1 < n; r += rnd.next(2, 3)) {
            int gap = rnd.next(m);
            for (int c = 0; c < m; ++c) {
                if (c != gap) grid[r][c] = '1';
            }
        }
    } else {
        for (int c = 1; c + 1 < m; c += rnd.next(2, 3)) {
            int gap = rnd.next(n);
            for (int r = 0; r < n; ++r) {
                if (r != gap) grid[r][c] = '1';
            }
        }
    }
    keepEndpointsOpen(grid);
    return grid;
}

static vector<string> checkerGrid(int n, int m) {
    vector<string> grid(n, string(m, '0'));
    int offset = rnd.next(2);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if ((r + c + offset) % 2 == 0) {
                grid[r][c] = '1';
            }
        }
    }
    keepEndpointsOpen(grid);
    return grid;
}

static vector<string> corridorGrid(int n, int m) {
    vector<string> grid(n, string(m, '1'));
    int r = 0;
    int c = 0;
    grid[r][c] = '0';
    while (r != n - 1 || c != m - 1) {
        bool moveDown;
        if (r == n - 1) {
            moveDown = false;
        } else if (c == m - 1) {
            moveDown = true;
        } else {
            moveDown = rnd.next(2) == 0;
        }

        if (moveDown) {
            ++r;
        } else {
            ++c;
        }
        grid[r][c] = '0';

        if (rnd.next(100) < 35) {
            vector<pair<int, int> > around;
            if (r > 0) around.push_back({r - 1, c});
            if (c > 0) around.push_back({r, c - 1});
            if (r + 1 < n) around.push_back({r + 1, c});
            if (c + 1 < m) around.push_back({r, c + 1});
            if (!around.empty()) {
                pair<int, int> cell = rnd.any(around);
                grid[cell.first][cell.second] = '0';
            }
        }
    }
    keepEndpointsOpen(grid);
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string shape = rnd.next("tiny|line|wide|tall|small|medium");
    int n;
    int m;
    if (shape == "tiny") {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else if (shape == "line") {
        if (rnd.next(2) == 0) {
            n = 1;
            m = rnd.next(2, 20);
        } else {
            n = rnd.next(2, 20);
            m = 1;
        }
    } else if (shape == "wide") {
        n = rnd.next(2, 5);
        m = rnd.next(8, 20);
    } else if (shape == "tall") {
        n = rnd.next(8, 20);
        m = rnd.next(2, 5);
    } else if (shape == "small") {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else {
        n = rnd.next(8, 16);
        m = rnd.next(8, 16);
    }

    int k = rnd.next(1, 10);
    int mode = rnd.next(4);
    vector<string> grid;
    if (mode == 0) {
        grid = randomGrid(n, m);
    } else if (mode == 1) {
        grid = barrierGrid(n, m);
    } else if (mode == 2) {
        grid = checkerGrid(n, m);
    } else {
        grid = corridorGrid(n, m);
    }

    println(n, m, k);
    for (const string& row : grid) {
        printf("%s\n", row.c_str());
    }

    return 0;
}
