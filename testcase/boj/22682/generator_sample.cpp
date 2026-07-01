#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

using Grid = vector<string>;

void printGrid(const Grid& grid) {
    println((int)grid[0].size(), (int)grid.size());
    for (const string& row : grid) {
        println(row);
    }
}

Grid randomGrid(int h, int w, int bWeight, int wWeight) {
    Grid grid(h, string(w, '.'));
    int total = bWeight + wWeight;
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            int roll = rnd.next(1, 100);
            if (roll <= total) {
                grid[r][c] = rnd.next(1, total) <= bWeight ? 'B' : 'W';
            }
        }
    }
    return grid;
}

Grid ringGrid(int h, int w, char color) {
    Grid grid(h, string(w, '.'));
    if (h == 1 || w == 1) {
        int count = h * w;
        int placed = rnd.next(1, count);
        for (int k = 0; k < placed; ++k) {
            int pos = rnd.next(0, count - 1);
            grid[pos / w][pos % w] = color;
        }
        return grid;
    }

    for (int c = 0; c < w; ++c) {
        grid[0][c] = color;
        grid[h - 1][c] = color;
    }
    for (int r = 0; r < h; ++r) {
        grid[r][0] = color;
        grid[r][w - 1] = color;
    }

    int holes = rnd.next(0, max(1, (h + w) / 4));
    for (int i = 0; i < holes; ++i) {
        int side = rnd.next(0, 3);
        if (side < 2) {
            int c = rnd.next(0, w - 1);
            grid[side == 0 ? 0 : h - 1][c] = '.';
        } else {
            int r = rnd.next(0, h - 1);
            grid[r][side == 2 ? 0 : w - 1] = '.';
        }
    }
    return grid;
}

Grid splitGrid(int h, int w) {
    Grid grid(h, string(w, '.'));
    if (rnd.next(0, 1) == 0) {
        int col = rnd.next(0, w - 1);
        for (int r = 0; r < h; ++r) {
            grid[r][col] = r % 2 == 0 ? 'B' : 'W';
        }
    } else {
        int row = rnd.next(0, h - 1);
        for (int c = 0; c < w; ++c) {
            grid[row][c] = c % 2 == 0 ? 'B' : 'W';
        }
    }
    return grid;
}

Grid corridorGrid(int h, int w) {
    Grid grid(h, string(w, '.'));
    int r = rnd.next(0, h - 1);
    int c = rnd.next(0, w - 1);
    char color = rnd.next(0, 1) == 0 ? 'B' : 'W';
    int steps = rnd.next(max(1, h + w), max(2, h * w / 2));
    for (int i = 0; i < steps; ++i) {
        grid[r][c] = color;
        if (rnd.next(0, 4) == 0) {
            color = color == 'B' ? 'W' : 'B';
        }
        int dir = rnd.next(0, 3);
        if (dir == 0 && r > 0) --r;
        if (dir == 1 && r + 1 < h) ++r;
        if (dir == 2 && c > 0) --c;
        if (dir == 3 && c + 1 < w) ++c;
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(4, 7);
    for (int tc = 0; tc < datasets; ++tc) {
        int mode = rnd.next(0, 5);
        int h;
        int w;
        Grid grid;

        if (mode == 0) {
            h = rnd.next(1, 4);
            w = rnd.next(1, 4);
            grid = randomGrid(h, w, rnd.next(5, 35), rnd.next(5, 35));
        } else if (mode == 1) {
            h = rnd.next(3, 9);
            w = rnd.next(3, 9);
            grid = ringGrid(h, w, rnd.next(0, 1) == 0 ? 'B' : 'W');
        } else if (mode == 2) {
            h = rnd.next(2, 10);
            w = rnd.next(2, 10);
            grid = splitGrid(h, w);
        } else if (mode == 3) {
            h = rnd.next(4, 12);
            w = rnd.next(4, 12);
            grid = corridorGrid(h, w);
        } else if (mode == 4) {
            h = rnd.next(6, 14);
            w = rnd.next(6, 14);
            grid = randomGrid(h, w, rnd.next(15, 45), rnd.next(15, 45));
        } else {
            h = rnd.next(1, 50);
            w = rnd.next(1, 50);
            grid = randomGrid(h, w, rnd.next(1, 20), rnd.next(1, 20));
        }

        printGrid(grid);
    }

    println(0, 0);
    return 0;
}
