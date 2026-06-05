#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

vector<string> emptyGrid(int n) {
    return vector<string>(n, string(n, '.'));
}

void clearCorners(vector<string>& grid) {
    int n = (int)grid.size();
    grid[0][0] = '.';
    grid[n - 1][n - 1] = '.';
}

vector<string> randomGrid(int n, double hayProbability) {
    vector<string> grid = emptyGrid(n);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (rnd.next() < hayProbability) {
                grid[r][c] = 'H';
            }
        }
    }
    clearCorners(grid);
    return grid;
}

void carvePath(vector<string>& grid, bool startRight) {
    int n = (int)grid.size();
    int r = 0;
    int c = 0;
    grid[r][c] = '.';

    while (r != n - 1 || c != n - 1) {
        bool canRight = c + 1 < n;
        bool canDown = r + 1 < n;
        bool goRight;

        if (!canDown) {
            goRight = true;
        } else if (!canRight) {
            goRight = false;
        } else if (r == 0 && c == 0) {
            goRight = startRight;
        } else {
            goRight = rnd.next(0, 1);
        }

        if (goRight) {
            ++c;
        } else {
            ++r;
        }
        grid[r][c] = '.';
    }
}

vector<string> corridorGrid(int n) {
    vector<string> grid(n, string(n, 'H'));
    carvePath(grid, rnd.next(0, 1));

    int extraOpen = rnd.next(0, n);
    for (int i = 0; i < extraOpen; ++i) {
        int r = rnd.next(0, n - 1);
        int c = rnd.next(0, n - 1);
        grid[r][c] = '.';
    }
    clearCorners(grid);
    return grid;
}

vector<string> patternedGrid(int n) {
    vector<string> grid = emptyGrid(n);
    int pattern = rnd.next(0, 2);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (pattern == 0 && (r + c) % 2 == 1 && rnd.next(0, 3) != 0) {
                grid[r][c] = 'H';
            } else if (pattern == 1 && r % 2 == 1 && c + 1 < n && rnd.next(0, 4) != 0) {
                grid[r][c] = 'H';
            } else if (pattern == 2 && c % 2 == 1 && r + 1 < n && rnd.next(0, 4) != 0) {
                grid[r][c] = 'H';
            }
        }
    }

    clearCorners(grid);
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 5) {
            n = rnd.next(20, 50);
        } else {
            n = rnd.next(2, 10);
        }
        int k = rnd.next(1, 3);

        vector<string> grid;
        if (mode == 0) {
            grid = emptyGrid(n);
        } else if (mode == 1) {
            grid = randomGrid(n, rnd.next(0.10, 0.35));
        } else if (mode == 2) {
            grid = randomGrid(n, rnd.next(0.45, 0.75));
        } else if (mode == 3) {
            grid = corridorGrid(n);
        } else if (mode == 4) {
            grid = patternedGrid(n);
        } else {
            grid = randomGrid(n, rnd.next(0.20, 0.55));
        }

        println(n, k);
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
