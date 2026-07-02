#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static vector<string> makeFilledGrid(int n, char fill) {
    return vector<string>(n, string(n, fill));
}

static void placeSink(vector<string>& grid) {
    int n = (int)grid.size();
    int r = rnd.next(n);
    int c = rnd.next(n);
    grid[r][c] = 'S';
}

static vector<string> openRoom(int n) {
    vector<string> grid = makeFilledGrid(n, '.');
    placeSink(grid);
    return grid;
}

static vector<string> randomWalls(int n) {
    vector<string> grid = makeFilledGrid(n, '.');
    int wallPercent = rnd.next(5, 65);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (rnd.next(100) < wallPercent) {
                grid[r][c] = '@';
            }
        }
    }
    placeSink(grid);
    return grid;
}

static vector<string> corridorGrid(int n) {
    vector<string> grid = makeFilledGrid(n, '@');
    int row = rnd.next(n);
    int col = rnd.next(n);

    for (int c = 0; c < n; ++c) {
        grid[row][c] = '.';
    }
    for (int r = 0; r < n; ++r) {
        grid[r][col] = '.';
    }

    int extraSegments = rnd.next(0, n);
    for (int i = 0; i < extraSegments; ++i) {
        if (rnd.next(2) == 0) {
            int r = rnd.next(n);
            int l = rnd.next(n);
            int rr = rnd.next(l, n - 1);
            for (int c = l; c <= rr; ++c) {
                grid[r][c] = '.';
            }
        } else {
            int c = rnd.next(n);
            int t = rnd.next(n);
            int b = rnd.next(t, n - 1);
            for (int r = t; r <= b; ++r) {
                grid[r][c] = '.';
            }
        }
    }

    placeSink(grid);
    return grid;
}

static vector<string> enclosedRoom(int n) {
    vector<string> grid = makeFilledGrid(n, '.');
    for (int i = 0; i < n; ++i) {
        grid[0][i] = '@';
        grid[n - 1][i] = '@';
        grid[i][0] = '@';
        grid[i][n - 1] = '@';
    }

    int innerWalls = rnd.next(0, n);
    for (int i = 0; i < innerWalls; ++i) {
        if (rnd.next(2) == 0) {
            int r = rnd.next(1, n - 2);
            int l = rnd.next(1, n - 2);
            int rr = rnd.next(l, n - 2);
            for (int c = l; c <= rr; ++c) {
                grid[r][c] = '@';
            }
        } else {
            int c = rnd.next(1, n - 2);
            int t = rnd.next(1, n - 2);
            int b = rnd.next(t, n - 2);
            for (int r = t; r <= b; ++r) {
                grid[r][c] = '@';
            }
        }
    }

    int sr = rnd.next(1, n - 2);
    int sc = rnd.next(1, n - 2);
    grid[sr][sc] = 'S';
    return grid;
}

static vector<string> diagonalBarriers(int n) {
    vector<string> grid = makeFilledGrid(n, '.');
    for (int i = 0; i < n; ++i) {
        if (rnd.next(100) < 75) {
            grid[i][i] = '@';
        }
        if (rnd.next(100) < 45) {
            grid[i][n - 1 - i] = '@';
        }
    }

    int holes = rnd.next(1, max(1, n / 2));
    for (int i = 0; i < holes; ++i) {
        grid[rnd.next(n)][rnd.next(n)] = '.';
    }

    placeSink(grid);
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    vector<string> grid;

    if (mode == 0) {
        n = rnd.next(1, 3);
        grid = randomWalls(n);
    } else if (mode == 1) {
        n = rnd.next(2, 11);
        grid = openRoom(n);
    } else if (mode == 2) {
        n = rnd.next(2, 11);
        grid = randomWalls(n);
    } else if (mode == 3) {
        n = rnd.next(3, 11);
        grid = corridorGrid(n);
    } else if (mode == 4) {
        n = rnd.next(3, 11);
        grid = enclosedRoom(n);
    } else {
        n = rnd.next(2, 11);
        grid = diagonalBarriers(n);
    }

    println(n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
