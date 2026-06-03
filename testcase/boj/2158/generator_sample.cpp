#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomHeight(int low = -25, int high = 25) {
    return rnd.next(low, high);
}

void printCase(int v, const vector<vector<int>>& grid) {
    int r = (int)grid.size();
    int c = (int)grid[0].size();
    println(v, r, c);
    for (int i = 0; i < r; ++i) {
        println(grid[i]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int v = rnd.next(1, 1000000);
    int r = rnd.next(1, 10);
    int c = rnd.next(1, 10);

    if (mode == 0) {
        r = rnd.next(1, 3);
        c = rnd.next(1, 3);
        v = rnd.any(vector<int>{1, 2, 3, 999999, 1000000});
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            r = 1;
            c = rnd.next(2, 20);
        } else {
            r = rnd.next(2, 20);
            c = 1;
        }
    } else if (mode == 5) {
        r = rnd.next(8, 18);
        c = rnd.next(8, 18);
    }

    vector<vector<int>> grid(r, vector<int>(c));

    if (mode == 0) {
        int low = randomHeight(-25, 0);
        int high = randomHeight(0, 25);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = rnd.any(vector<int>{-25, low, 0, high, 25});
            }
        }
    } else if (mode == 1) {
        int current = randomHeight();
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                current = max(-25, min(25, current + rnd.next(-8, 8)));
                grid[i][j] = current;
            }
        }
    } else if (mode == 2) {
        int base = randomHeight(-15, 15);
        int rowStep = rnd.next(-4, 4);
        int colStep = rnd.next(-4, 4);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = max(-25, min(25, base + i * rowStep + j * colStep));
            }
        }
    } else if (mode == 3) {
        int a = randomHeight(-25, -5);
        int b = randomHeight(5, 25);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = ((i + j) % 2 == 0 ? a : b);
            }
        }
    } else if (mode == 4) {
        int wall = rnd.any(vector<int>{-25, 25});
        int path = -wall;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                grid[i][j] = wall;
            }
        }
        int x = 0;
        int y = 0;
        grid[x][y] = path;
        while (x != r - 1 || y != c - 1) {
            if (x == r - 1) {
                ++y;
            } else if (y == c - 1) {
                ++x;
            } else if (rnd.next(0, 1) == 0) {
                ++x;
            } else {
                ++y;
            }
            grid[x][y] = path + rnd.next(-2, 2);
            grid[x][y] = max(-25, min(25, grid[x][y]));
        }
    } else {
        int low = randomHeight(-25, -10);
        int high = randomHeight(10, 25);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (i == 0 && j == 0) {
                    grid[i][j] = rnd.any(vector<int>{low, high, 0});
                } else if (i == r - 1 && j == c - 1) {
                    grid[i][j] = rnd.any(vector<int>{low, high, 0});
                } else {
                    grid[i][j] = rnd.next() < 0.75 ? randomHeight(low, high) : rnd.any(vector<int>{-25, 25});
                }
            }
        }
    }

    printCase(v, grid);
    return 0;
}
