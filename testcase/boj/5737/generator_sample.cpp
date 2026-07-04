#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static vector<string> makeGrid(int r, int c, int mode) {
    vector<string> grid(r, string(c, '.'));

    if (mode == 0) {
        double gearProb = rnd.next(0.05, 0.25);
        double activeProb = rnd.next(0.05, 0.30);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (rnd.next() < gearProb) {
                    grid[i][j] = rnd.next() < activeProb ? 'I' : '*';
                }
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if ((i + j) % 2 == 0 && rnd.next() < 0.75) {
                    grid[i][j] = rnd.next() < 0.20 ? 'I' : '*';
                }
            }
        }
    } else if (mode == 2) {
        double activeProb = rnd.next(0.15, 0.45);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (rnd.next() < 0.75) {
                    grid[i][j] = rnd.next() < activeProb ? 'I' : '*';
                }
            }
        }
    } else if (mode == 3) {
        int patches = rnd.next(1, 4);
        for (int p = 0; p < patches; ++p) {
            int r1 = rnd.next(0, r - 1);
            int r2 = rnd.next(r1, r - 1);
            int c1 = rnd.next(0, c - 1);
            int c2 = rnd.next(c1, c - 1);
            for (int i = r1; i <= r2; ++i) {
                for (int j = c1; j <= c2; ++j) {
                    if (rnd.next() < 0.85) {
                        grid[i][j] = rnd.next() < 0.25 ? 'I' : '*';
                    }
                }
            }
        }
    } else {
        int gears = rnd.next(1, r * c);
        for (int k = 0; k < gears; ++k) {
            int i = rnd.next(0, r - 1);
            int j = rnd.next(0, c - 1);
            grid[i][j] = rnd.next() < 0.50 ? 'I' : '*';
        }
    }

    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(4, 9);
    for (int tc = 0; tc < testCases; ++tc) {
        int mode = rnd.next(0, 4);
        int r;
        int c;

        if (tc == 0) {
            r = 1;
            c = rnd.next(1, 12);
        } else if (tc == 1) {
            r = rnd.next(1, 12);
            c = 1;
        } else if (tc == 2) {
            r = rnd.next(2, 4);
            c = rnd.next(2, 4);
        } else {
            r = rnd.next(3, 12);
            c = rnd.next(3, 12);
        }

        println(r, c);
        vector<string> grid = makeGrid(r, c, mode);
        for (const string& row : grid) {
            println(row);
        }
    }

    println(0, 0);
    return 0;
}
