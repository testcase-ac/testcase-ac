#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static vector<string> makeChecker(int n, int m) {
    vector<string> grid(n, string(m, 'B'));
    int offset = rnd.next(0, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = ((i + j + offset) % 2 == 0 ? 'B' : 'W');
        }
    }
    return grid;
}

static vector<string> makeStripes(int n, int m, bool horizontal) {
    vector<string> grid(n, string(m, 'B'));
    int band = rnd.next(1, 3);
    int offset = rnd.next(0, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int index = horizontal ? i : j;
            grid[i][j] = ((index / band + offset) % 2 == 0 ? 'B' : 'W');
        }
    }
    return grid;
}

static vector<string> makeIslands(int n, int m) {
    char background = rnd.next(0, 1) ? 'B' : 'W';
    char island = background == 'B' ? 'W' : 'B';
    vector<string> grid(n, string(m, background));

    int rectangles = rnd.next(1, min(8, n * m));
    for (int r = 0; r < rectangles; ++r) {
        int r1 = rnd.next(0, n - 1);
        int c1 = rnd.next(0, m - 1);
        int r2 = rnd.next(r1, min(n - 1, r1 + rnd.next(0, 3)));
        int c2 = rnd.next(c1, min(m - 1, c1 + rnd.next(0, 3)));
        for (int i = r1; i <= r2; ++i) {
            for (int j = c1; j <= c2; ++j) {
                grid[i][j] = island;
            }
        }
    }

    return grid;
}

static vector<string> makeBiasedRandom(int n, int m) {
    vector<string> grid(n, string(m, 'B'));
    int threshold = rnd.next(15, 85);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = (rnd.next(1, 100) <= threshold ? 'B' : 'W');
        }
    }
    return grid;
}

static vector<string> makeSymmetric(int n, int m) {
    vector<string> grid(n, string(m, 'B'));
    int halfRows = (n + 1) / 2;
    int halfCols = (m + 1) / 2;
    for (int i = 0; i < halfRows; ++i) {
        for (int j = 0; j < halfCols; ++j) {
            char color = rnd.next(0, 1) ? 'B' : 'W';
            grid[i][j] = color;
            grid[n - 1 - i][j] = color;
            grid[i][m - 1 - j] = color;
            grid[n - 1 - i][m - 1 - j] = color;
        }
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 10);
    int m = rnd.next(2, 10);

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 24);
    } else if (mode == 1) {
        n = rnd.next(1, 24);
        m = 1;
    } else if (mode == 6) {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
    }

    vector<string> grid;
    if (mode == 0 || mode == 1) {
        grid = makeStripes(n, m, mode == 1);
        if (rnd.next(0, 1)) {
            grid = makeChecker(n, m);
        }
    } else if (mode == 2) {
        grid = makeChecker(n, m);
    } else if (mode == 3) {
        grid = makeStripes(n, m, rnd.next(0, 1));
    } else if (mode == 4) {
        grid = makeIslands(n, m);
    } else if (mode == 5) {
        grid = makeSymmetric(n, m);
    } else {
        grid = makeBiasedRandom(n, m);
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
