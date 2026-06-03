#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using Grid = vector<vector<int>>;

Grid randomGrid(int r, int c) {
    int fencePercent = rnd.next(5, 85);
    Grid grid(r, vector<int>(c));
    bool hasZero = false;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            grid[i][j] = rnd.next(1, 100) <= fencePercent;
            hasZero = hasZero || grid[i][j] == 0;
        }
    }
    if (!hasZero) {
        grid[rnd.next(r)][rnd.next(c)] = 0;
    }
    return grid;
}

Grid ringGrid(int r, int c) {
    Grid grid(r, vector<int>(c, 0));
    int layers = rnd.next(1, max(1, min(r, c) / 2 - 1));

    for (int layer = 0; layer < layers; ++layer) {
        int top = layer;
        int bottom = r - 1 - layer;
        int left = layer;
        int right = c - 1 - layer;
        for (int j = left; j <= right; ++j) {
            grid[top][j] = 1;
            grid[bottom][j] = 1;
        }
        for (int i = top; i <= bottom; ++i) {
            grid[i][left] = 1;
            grid[i][right] = 1;
        }

        int side = rnd.next(4);
        if (side == 0) grid[top][rnd.next(left, right)] = 0;
        if (side == 1) grid[bottom][rnd.next(left, right)] = 0;
        if (side == 2) grid[rnd.next(top, bottom)][left] = 0;
        if (side == 3) grid[rnd.next(top, bottom)][right] = 0;
    }

    int innerTop = layers;
    int innerBottom = r - 1 - layers;
    int innerLeft = layers;
    int innerRight = c - 1 - layers;
    if (innerTop <= innerBottom && innerLeft <= innerRight) {
        for (int i = innerTop; i <= innerBottom; ++i) {
            for (int j = innerLeft; j <= innerRight; ++j) {
                grid[i][j] = 0;
            }
        }
    }
    return grid;
}

Grid stripeGrid(int r, int c) {
    Grid grid(r, vector<int>(c, 0));
    bool vertical = rnd.next(2);
    int step = rnd.next(2, 4);

    if (vertical) {
        for (int j = rnd.next(1, step); j < c; j += step) {
            for (int i = 0; i < r; ++i) grid[i][j] = 1;
            int gaps = rnd.next(1, max(1, r / 3));
            for (int k = 0; k < gaps; ++k) grid[rnd.next(r)][j] = 0;
        }
    } else {
        for (int i = rnd.next(1, step); i < r; i += step) {
            for (int j = 0; j < c; ++j) grid[i][j] = 1;
            int gaps = rnd.next(1, max(1, c / 3));
            for (int k = 0; k < gaps; ++k) grid[i][rnd.next(c)] = 0;
        }
    }
    return grid;
}

Grid blockGrid(int r, int c) {
    Grid grid(r, vector<int>(c, 1));
    int rooms = rnd.next(2, 6);
    for (int room = 0; room < rooms; ++room) {
        int h = rnd.next(1, max(1, r / 2));
        int w = rnd.next(1, max(1, c / 2));
        int top = rnd.next(0, r - h);
        int left = rnd.next(0, c - w);
        for (int i = top; i < top + h; ++i) {
            for (int j = left; j < left + w; ++j) {
                grid[i][j] = 0;
            }
        }
    }

    int corridorCount = rnd.next(1, 4);
    for (int k = 0; k < corridorCount; ++k) {
        if (rnd.next(2)) {
            int row = rnd.next(r);
            for (int j = 0; j < c; ++j) grid[row][j] = 0;
        } else {
            int col = rnd.next(c);
            for (int i = 0; i < r; ++i) grid[i][col] = 0;
        }
    }
    return grid;
}

Grid makeGrid(int r, int c) {
    int mode = rnd.next(5);
    if (mode == 0) return Grid(r, vector<int>(c, 0));
    if (mode == 1) return randomGrid(r, c);
    if (mode == 2) return ringGrid(r, c);
    if (mode == 3) return stripeGrid(r, c);
    return blockGrid(r, c);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int r = rnd.next(5, 14);
        int c = rnd.next(5, 16);
        Grid grid = makeGrid(r, c);

        println(r, c);
        for (int i = 0; i < r; ++i) {
            println(grid[i]);
        }
    }

    return 0;
}
