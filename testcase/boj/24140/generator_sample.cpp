#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Rect {
    int r1;
    int c1;
    int r2;
    int c2;
};

Rect randomRect(int h, int w, int mode) {
    if (mode == 1) {
        int r = rnd.next(0, h - 1);
        int c1 = rnd.next(0, w - 1);
        int c2 = rnd.next(c1, w - 1);
        return {r, c1, r, c2};
    }
    if (mode == 2) {
        int c = rnd.next(0, w - 1);
        int r1 = rnd.next(0, h - 1);
        int r2 = rnd.next(r1, h - 1);
        return {r1, c, r2, c};
    }
    if (mode == 3) {
        int r1 = rnd.next(0, h - 1);
        int c1 = rnd.next(0, w - 1);
        int r2 = rnd.next(r1, min(h - 1, r1 + rnd.next(0, 2)));
        int c2 = rnd.next(c1, min(w - 1, c1 + rnd.next(0, 2)));
        return {r1, c1, r2, c2};
    }

    int r1 = rnd.next(0, h - 1);
    int r2 = rnd.next(r1, h - 1);
    int c1 = rnd.next(0, w - 1);
    int c2 = rnd.next(c1, w - 1);
    return {r1, c1, r2, c2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int w = rnd.next(1, 10);
    int h = rnd.next(1, 10);
    int n = rnd.next(1, 18);

    if (mode == 0) {
        w = rnd.next(1, 4);
        h = rnd.next(1, 4);
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        w = rnd.next(5, 12);
        h = rnd.next(5, 12);
        n = rnd.next(8, 25);
    } else if (mode == 2) {
        w = rnd.next(1, 14);
        h = rnd.next(1, 14);
        n = rnd.next(4, 20);
    } else if (mode == 3) {
        w = rnd.next(8, 20);
        h = rnd.next(2, 8);
        n = rnd.next(6, 30);
    } else if (mode == 4) {
        w = rnd.next(2, 8);
        h = rnd.next(8, 20);
        n = rnd.next(6, 30);
    } else {
        w = rnd.next(8, 25);
        h = rnd.next(8, 25);
        n = rnd.next(20, 60);
    }

    vector<int> colors(n);
    iota(colors.begin(), colors.end(), 1);
    shuffle(colors.begin(), colors.end());

    vector<vector<int>> grid(h, vector<int>(w, 0));
    for (int i = 0; i < n; ++i) {
        int shapeMode = 0;
        if (mode == 2) shapeMode = rnd.next(1, 2);
        else if (mode == 3) shapeMode = 1;
        else if (mode == 4) shapeMode = 2;
        else if (mode == 0) shapeMode = rnd.next(0, 3);
        else shapeMode = rnd.next(0, 4);

        Rect rect = randomRect(h, w, shapeMode);

        if (mode == 1 && i > 0 && rnd.next(0, 4) == 0) {
            rect = {0, 0, h - 1, w - 1};
        }

        for (int r = rect.r1; r <= rect.r2; ++r) {
            for (int c = rect.c1; c <= rect.c2; ++c) {
                grid[r][c] = colors[i];
            }
        }
    }

    println(n, w, h);
    for (const vector<int>& row : grid) {
        println(row);
    }

    return 0;
}
