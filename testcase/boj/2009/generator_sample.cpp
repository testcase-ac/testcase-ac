#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

using Grid = vector<string>;

Grid makeGrid(int n, char value) {
    return Grid(n, string(n, value));
}

void projectCube(const vector<Grid>& cube, Grid& h, Grid& r, Grid& c) {
    int n = (int)cube.size();
    h = makeGrid(n, '0');
    r = makeGrid(n, '0');
    c = makeGrid(n, '0');

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (cube[i][j][k] == '1') {
                    h[j][k] = '1';
                    r[i][k] = '1';
                    c[i][j] = '1';
                }
            }
        }
    }
}

Grid randomGrid(int n, int percentOnes) {
    Grid grid = makeGrid(n, '0');
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (rnd.next(100) < percentOnes) {
                grid[i][j] = '1';
            }
        }
    }
    return grid;
}

void printInput(const Grid& h, const Grid& r, const Grid& c) {
    println((int)h.size());
    for (const string& row : h) println(row);
    for (const string& row : r) println(row);
    for (const string& row : c) println(row);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 6) {
        n = rnd.next(20, 100);
    } else {
        n = rnd.next(2, 12);
    }

    Grid h, r, c;

    if (mode == 0) {
        char bit = rnd.next(2) ? '1' : '0';
        h = makeGrid(n, bit);
        r = makeGrid(n, bit);
        c = makeGrid(n, bit);
    } else if (mode == 1) {
        vector<Grid> cube(n, makeGrid(n, '0'));
        int cells = rnd.next(1, n * n);
        for (int t = 0; t < cells; ++t) {
            int i = rnd.next(n);
            int j = rnd.next(n);
            int k = rnd.next(n);
            cube[i][j][k] = '1';
        }
        projectCube(cube, h, r, c);
    } else if (mode == 2) {
        vector<Grid> cube(n, makeGrid(n, '0'));
        int percentOnes = rnd.next(10, 55);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (rnd.next(100) < percentOnes) {
                        cube[i][j][k] = '1';
                    }
                }
            }
        }
        projectCube(cube, h, r, c);
    } else if (mode == 3) {
        h = randomGrid(n, rnd.next(10, 80));
        r = randomGrid(n, rnd.next(10, 80));
        c = randomGrid(n, rnd.next(10, 80));
    } else if (mode == 4) {
        h = makeGrid(n, '0');
        r = makeGrid(n, '0');
        c = makeGrid(n, '0');
        int i = rnd.next(n);
        int j = rnd.next(n);
        int k = rnd.next(n);
        h[j][k] = '1';
        r[i][k] = '1';
        c[i][j] = '1';

        if (rnd.next(2)) {
            h[rnd.next(n)][rnd.next(n)] = '1';
        } else {
            r[rnd.next(n)][rnd.next(n)] = '1';
        }
    } else if (mode == 5) {
        h = makeGrid(n, '0');
        r = makeGrid(n, '0');
        c = makeGrid(n, '0');
        int i = rnd.next(n);
        int j = rnd.next(n);
        for (int k = 0; k < n; ++k) {
            if (rnd.next(100) < 70) {
                h[j][k] = '1';
                r[i][k] = '1';
            }
        }
        c[i][j] = '1';
    } else {
        h = makeGrid(n, '1');
        r = makeGrid(n, '1');
        c = makeGrid(n, '1');
        int holes = rnd.next(1, n);
        for (int t = 0; t < holes; ++t) {
            h[rnd.next(n)][rnd.next(n)] = '0';
            r[rnd.next(n)][rnd.next(n)] = '0';
            c[rnd.next(n)][rnd.next(n)] = '0';
        }
    }

    printInput(h, r, c);
    return 0;
}
