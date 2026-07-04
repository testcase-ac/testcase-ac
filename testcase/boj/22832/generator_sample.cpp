#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Pos {
    int r;
    int c;
};

void placeDistinct(vector<vector<int>>& grid, vector<Pos> cells) {
    shuffle(cells.begin(), cells.end());
    ensuref(int(cells.size()) >= 3, "not enough empty cells to place objects");
    grid[cells[0].r][cells[0].c] = 2;
    grid[cells[1].r][cells[1].c] = 3;
    grid[cells[2].r][cells[2].c] = 4;
}

vector<Pos> emptyCells(const vector<vector<int>>& grid) {
    vector<Pos> cells;
    for (int r = 0; r < int(grid.size()); ++r) {
        for (int c = 0; c < int(grid[r].size()); ++c) {
            if (grid[r][c] == 0) {
                cells.push_back({r, c});
            }
        }
    }
    return cells;
}

vector<vector<int>> makeOpenRoom(int h, int w) {
    vector<vector<int>> grid(h, vector<int>(w, 0));
    int pillars = rnd.next(0, max(0, h * w / 4));
    vector<Pos> cells = emptyCells(grid);
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < pillars && i + 3 < int(cells.size()); ++i) {
        grid[cells[i].r][cells[i].c] = 1;
    }
    placeDistinct(grid, emptyCells(grid));
    return grid;
}

vector<vector<int>> makeCorridor(int h, int w) {
    vector<vector<int>> grid(h, vector<int>(w, 1));
    int row = rnd.next(h);
    for (int c = 0; c < w; ++c) {
        grid[row][c] = 0;
    }
    for (int r = 0; r < h; ++r) {
        grid[r][rnd.next(w)] = 0;
    }
    while (int(emptyCells(grid).size()) < 3) {
        grid[rnd.next(h)][rnd.next(w)] = 0;
    }
    placeDistinct(grid, emptyCells(grid));
    return grid;
}

vector<vector<int>> makeCornerCase(int h, int w) {
    vector<vector<int>> grid(h, vector<int>(w, 0));
    if (h >= 2 && w >= 2 && h * w >= 5) {
        int corner = rnd.next(4);
        int cr = corner < 2 ? 0 : h - 1;
        int cc = corner % 2 == 0 ? 0 : w - 1;
        int vr = cr == 0 ? 1 : h - 2;
        int hc = cc == 0 ? 1 : w - 2;
        grid[vr][cc] = 1;
        grid[cr][hc] = 1;
    }
    int extra = rnd.next(0, max(0, h * w / 5));
    vector<Pos> cells = emptyCells(grid);
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < extra && i + 3 < int(cells.size()); ++i) {
        grid[cells[i].r][cells[i].c] = 1;
    }
    placeDistinct(grid, emptyCells(grid));
    return grid;
}

void printMap(const vector<vector<int>>& grid) {
    int h = int(grid.size());
    int w = int(grid[0].size());
    println(w, h);
    for (int r = 0; r < h; ++r) {
        println(grid[r]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int maps = rnd.next(1, 5);
    for (int i = 0; i < maps; ++i) {
        int h = rnd.next(1, 7);
        int w = rnd.next(max(1, (3 + h - 1) / h), 7);
        int mode = rnd.next(3);

        if (mode == 0) {
            printMap(makeOpenRoom(h, w));
        } else if (mode == 1) {
            printMap(makeCorridor(h, w));
        } else {
            printMap(makeCornerCase(h, w));
        }
    }
    println(0, 0);
    return 0;
}
