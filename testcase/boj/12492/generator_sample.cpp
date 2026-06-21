#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

vector<string> makeGrid(int r, int c, char fill = '.') {
    return vector<string>(r, string(c, fill));
}

void addTileableBlocks(vector<string>& grid, double blockProb) {
    int r = (int)grid.size();
    int c = (int)grid[0].size();

    for (int i = 0; i + 1 < r; i += 2) {
        for (int j = 0; j + 1 < c; j += 2) {
            if (rnd.next() < blockProb) {
                grid[i][j] = '#';
                grid[i + 1][j] = '#';
                grid[i][j + 1] = '#';
                grid[i + 1][j + 1] = '#';
            }
        }
    }
}

void addRandomHashes(vector<string>& grid, double hashProb) {
    for (string& row : grid) {
        for (char& ch : row) {
            if (rnd.next() < hashProb) {
                ch = '#';
            }
        }
    }
}

void printCase(const vector<string>& grid) {
    println((int)grid.size(), (int)grid[0].size());
    for (const string& row : grid) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 6);
        int r;
        int c;
        vector<string> grid;

        if (mode == 0) {
            r = rnd.next(1, 4);
            c = rnd.next(1, 4);
            grid = makeGrid(r, c);
            if (rnd.next(0, 1) == 1) {
                grid[rnd.next(r)][rnd.next(c)] = '#';
            }
        } else if (mode == 1) {
            r = rnd.next(2, 12);
            c = rnd.next(2, 12);
            grid = makeGrid(r, c);
            addTileableBlocks(grid, rnd.next(0.25, 0.95));
        } else if (mode == 2) {
            r = rnd.next(2, 12);
            c = rnd.next(2, 12);
            grid = makeGrid(r, c);
            addTileableBlocks(grid, rnd.next(0.45, 0.9));
            grid[rnd.next(r)][rnd.next(c)] = '#';
        } else if (mode == 3) {
            r = rnd.next(1, 12);
            c = rnd.next(1, 12);
            grid = makeGrid(r, c);
            addRandomHashes(grid, rnd.next(0.15, 0.75));
        } else if (mode == 4) {
            r = rnd.next(2, 10);
            c = rnd.next(2, 10);
            grid = makeGrid(r, c);
            int stripeCount = rnd.next(1, max(r, c));
            for (int k = 0; k < stripeCount; ++k) {
                if (rnd.next(0, 1) == 0) {
                    int row = rnd.next(r);
                    for (int j = 0; j < c; ++j) {
                        grid[row][j] = '#';
                    }
                } else {
                    int col = rnd.next(c);
                    for (int i = 0; i < r; ++i) {
                        grid[i][col] = '#';
                    }
                }
            }
        } else if (mode == 5) {
            r = rnd.next(45, 50);
            c = rnd.next(45, 50);
            grid = makeGrid(r, c);
            addTileableBlocks(grid, rnd.next(0.05, 0.2));
        } else {
            r = rnd.next(45, 50);
            c = rnd.next(45, 50);
            grid = makeGrid(r, c);
            addRandomHashes(grid, rnd.next(0.02, 0.08));
        }

        printCase(grid);
    }

    return 0;
}
