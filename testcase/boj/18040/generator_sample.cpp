#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static vector<string> makeGrid(int n, int m, char fill) {
    return vector<string>(n, string(m, fill));
}

static void addNoise(vector<string>& grid, int flips) {
    int n = (int)grid.size();
    int m = (int)grid[0].size();
    for (int k = 0; k < flips; ++k) {
        int r = rnd.next(0, n - 1);
        int c = rnd.next(0, m - 1);
        grid[r][c] = grid[r][c] == 'G' ? 'B' : 'G';
    }
}

static vector<string> makeUniform(int n, int m) {
    return makeGrid(n, m, rnd.next(0, 1) == 0 ? 'G' : 'B');
}

static vector<string> makeChecker(int n, int m) {
    vector<string> grid = makeGrid(n, m, 'G');
    int shift = rnd.next(0, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = ((i + j + shift) % 2 == 0) ? 'G' : 'B';
        }
    }
    return grid;
}

static vector<string> makeStripes(int n, int m) {
    vector<string> grid = makeGrid(n, m, 'G');
    bool horizontal = rnd.next(0, 1) == 0;
    int width = rnd.next(1, 3);
    int shift = rnd.next(0, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int band = horizontal ? i / width : j / width;
            grid[i][j] = ((band + shift) % 2 == 0) ? 'G' : 'B';
        }
    }
    return grid;
}

static vector<string> makeFrame(int n, int m) {
    vector<string> grid = makeGrid(n, m, 'B');
    int layers = rnd.next(1, max(1, min(n, m) / 2));
    for (int layer = 0; layer < layers; ++layer) {
        char value = (layer % 2 == 0) ? 'G' : 'B';
        for (int i = layer; i < n - layer; ++i) {
            grid[i][layer] = value;
            grid[i][m - 1 - layer] = value;
        }
        for (int j = layer; j < m - layer; ++j) {
            grid[layer][j] = value;
            grid[n - 1 - layer][j] = value;
        }
    }
    return grid;
}

static vector<string> makeBlocks(int n, int m) {
    vector<string> grid = makeGrid(n, m, 'G');
    int rowBlock = rnd.next(1, 4);
    int colBlock = rnd.next(1, 4);
    int shift = rnd.next(0, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int blockParity = i / rowBlock + j / colBlock + shift;
            grid[i][j] = (blockParity % 2 == 0) ? 'G' : 'B';
        }
    }
    return grid;
}

static vector<string> makeRandom(int n, int m) {
    vector<string> grid = makeGrid(n, m, 'G');
    int goodPercent = rnd.next(15, 85);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = rnd.next(1, 100) <= goodPercent ? 'G' : 'B';
        }
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    if (mode == 0) {
        n = rnd.next(1, 14);
        m = rnd.next(1, 14);
    } else if (mode == 1) {
        n = rnd.next(1, 18);
        m = rnd.next(1, 18);
    } else if (mode == 2) {
        n = rnd.next(1, 18);
        m = rnd.next(1, 18);
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        m = rnd.next(2, 18);
    } else if (mode == 4) {
        n = rnd.next(3, 18);
        m = rnd.next(3, 18);
    } else if (mode == 5) {
        n = rnd.next(4, 20);
        m = rnd.next(4, 20);
    } else {
        if (rnd.next(0, 1) == 0) {
            n = 1;
            m = rnd.next(1, 30);
        } else {
            n = rnd.next(1, 30);
            m = 1;
        }
    }

    vector<string> grid;
    if (mode == 0) {
        grid = makeUniform(n, m);
        addNoise(grid, rnd.next(0, min(6, n * m)));
    } else if (mode == 1) {
        grid = makeChecker(n, m);
    } else if (mode == 2) {
        grid = makeStripes(n, m);
        addNoise(grid, rnd.next(0, min(5, n * m)));
    } else if (mode == 3) {
        grid = makeFrame(n, m);
    } else if (mode == 4) {
        grid = makeBlocks(n, m);
        addNoise(grid, rnd.next(0, min(8, n * m)));
    } else if (mode == 5) {
        grid = makeRandom(n, m);
    } else {
        grid = makeChecker(n, m);
        addNoise(grid, rnd.next(0, min(4, n * m)));
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
