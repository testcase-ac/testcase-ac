#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Rect {
    int r1;
    int c1;
    int r2;
    int c2;
    char ch;
};

static void paintRect(vector<string>& grid, const Rect& rect) {
    for (int r = rect.r1; r <= rect.r2; ++r) {
        for (int c = rect.c1; c <= rect.c2; ++c) {
            grid[r][c] = rect.ch;
        }
    }
}

static Rect randomRect(int h, int w, char ch) {
    int r1 = rnd.next(0, h - 1);
    int r2 = rnd.next(r1, h - 1);
    int c1 = rnd.next(0, w - 1);
    int c2 = rnd.next(c1, w - 1);
    return {r1, c1, r2, c2, ch};
}

static vector<string> makeEmptyOrSingle(int h, int w) {
    vector<string> grid(h, string(w, '.'));
    if (rnd.next(2) == 1) {
        paintRect(grid, randomRect(h, w, 'A'));
    }
    return grid;
}

static vector<string> makeLayeredRectangles(int h, int w) {
    vector<string> grid(h, string(w, '.'));
    int materialCount = rnd.next(2, min(7, max(2, h * w)));
    vector<Rect> rects;
    for (int i = 0; i < materialCount; ++i) {
        rects.push_back(randomRect(h, w, char('A' + i)));
    }
    shuffle(rects.begin(), rects.end());
    for (const Rect& rect : rects) {
        paintRect(grid, rect);
    }
    return grid;
}

static vector<string> makeStripeOcclusion(int h, int w) {
    vector<string> grid(h, string(w, '.'));
    int materials = rnd.next(2, min(7, max(2, min(h, w) + 1)));
    for (int i = 0; i < materials; ++i) {
        char ch = char('A' + i);
        if (rnd.next(2) == 0) {
            int r1 = rnd.next(0, h - 1);
            int r2 = rnd.next(r1, h - 1);
            int c = rnd.next(0, w - 1);
            int width = rnd.next(1, min(3, w - c));
            paintRect(grid, {r1, c, r2, c + width - 1, ch});
        } else {
            int c1 = rnd.next(0, w - 1);
            int c2 = rnd.next(c1, w - 1);
            int r = rnd.next(0, h - 1);
            int height = rnd.next(1, min(3, h - r));
            paintRect(grid, {r, c1, r + height - 1, c2, ch});
        }
    }
    return grid;
}

static vector<string> makeMissingCornerShape(int h, int w) {
    h = max(h, 2);
    w = max(w, 2);
    vector<string> grid(h, string(w, '.'));

    int r1 = rnd.next(0, h - 2);
    int r2 = rnd.next(r1 + 1, h - 1);
    int c1 = rnd.next(0, w - 2);
    int c2 = rnd.next(c1 + 1, w - 1);
    paintRect(grid, {r1, c1, r2, c2, 'A'});

    int corner = rnd.next(4);
    int cutR = (corner < 2 ? r1 : r2);
    int cutC = (corner % 2 == 0 ? c1 : c2);
    grid[cutR][cutC] = '.';

    if (rnd.next(2) == 1) {
        paintRect(grid, randomRect(h, w, 'B'));
    }
    return grid;
}

static vector<string> makeSparseLetters(int h, int w) {
    vector<string> grid(h, string(w, '.'));
    int cells = rnd.next(1, min(7, h * w));
    vector<int> positions;
    for (int i = 0; i < h * w; ++i) {
        positions.push_back(i);
    }
    shuffle(positions.begin(), positions.end());
    for (int i = 0; i < cells; ++i) {
        int pos = positions[i];
        grid[pos / w][pos % w] = char('A' + i);
    }
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 10);
    vector<vector<string>> cases;
    int totalArea = 0;

    for (int caseId = 0; caseId < t; ++caseId) {
        int mode = rnd.next(5);
        int h = rnd.next(1, 12);
        int w = rnd.next(1, 14);
        if (mode == 3) {
            h = rnd.next(2, 12);
            w = rnd.next(2, 14);
        }

        if (totalArea + h * w > 900) {
            h = rnd.next(1, 6);
            w = rnd.next(1, 8);
        }
        totalArea += h * w;

        if (mode == 0) {
            cases.push_back(makeEmptyOrSingle(h, w));
        } else if (mode == 1) {
            cases.push_back(makeLayeredRectangles(h, w));
        } else if (mode == 2) {
            cases.push_back(makeStripeOcclusion(h, w));
        } else if (mode == 3) {
            cases.push_back(makeMissingCornerShape(h, w));
        } else {
            cases.push_back(makeSparseLetters(h, w));
        }
    }

    println((int)cases.size());
    for (const vector<string>& grid : cases) {
        println((int)grid.size(), (int)grid[0].size());
        for (const string& row : grid) {
            println(row);
        }
    }

    return 0;
}
