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

const string LABELS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void paint(vector<string>& grid, const Rect& rect) {
    for (int r = rect.r1; r <= rect.r2; ++r) {
        for (int c = rect.c1; c <= rect.c2; ++c) {
            grid[r][c] = rect.ch;
        }
    }
}

void printGrid(const vector<string>& grid) {
    println((int)grid.size(), (int)grid[0].size());
    for (const string& row : grid) {
        println(row);
    }
}

Rect randomRect(int n, int m, char ch) {
    int r1 = rnd.next(0, n - 1);
    int r2 = rnd.next(r1, n - 1);
    int c1 = rnd.next(0, m - 1);
    int c2 = rnd.next(c1, m - 1);
    return {r1, c1, r2, c2, ch};
}

vector<string> layeredRectangles(int n, int m, int cardCount) {
    vector<string> grid(n, string(m, '.'));
    vector<Rect> cards;

    for (int i = 0; i < cardCount; ++i) {
        cards.push_back(randomRect(n, m, LABELS[i]));
    }

    int mode = rnd.next(0, 2);
    if (mode == 1) {
        sort(cards.begin(), cards.end(), [](const Rect& a, const Rect& b) {
            int areaA = (a.r2 - a.r1 + 1) * (a.c2 - a.c1 + 1);
            int areaB = (b.r2 - b.r1 + 1) * (b.c2 - b.c1 + 1);
            return areaA > areaB;
        });
    } else if (mode == 2) {
        shuffle(cards.begin(), cards.end());
    }

    for (const Rect& card : cards) {
        paint(grid, card);
    }
    return grid;
}

vector<string> nestedRectangles(int n, int m) {
    vector<string> grid(n, string(m, '.'));
    int layers = min({n, m, rnd.next(2, 5)});
    for (int i = 0; i < layers; ++i) {
        Rect rect{i, i, n - 1 - i, m - 1 - i, LABELS[i]};
        if (rect.r1 <= rect.r2 && rect.c1 <= rect.c2) {
            paint(grid, rect);
        }
    }
    return grid;
}

vector<string> invalidHole(int n, int m) {
    n = max(n, 3);
    m = max(m, 3);
    vector<string> grid(n, string(m, '.'));
    char outer = rnd.any(LABELS);

    int r1 = rnd.next(0, n - 3);
    int c1 = rnd.next(0, m - 3);
    int r2 = rnd.next(r1 + 2, n - 1);
    int c2 = rnd.next(c1 + 2, m - 1);

    paint(grid, {r1, c1, r2, c2, outer});
    grid[rnd.next(r1 + 1, r2 - 1)][rnd.next(c1 + 1, c2 - 1)] = '.';
    return grid;
}

vector<string> invalidCycle() {
    vector<string> grid(2, string(2, '.'));
    char a = rnd.any(LABELS);
    char b = rnd.any(LABELS);
    while (b == a) {
        b = rnd.any(LABELS);
    }
    grid[0][0] = a;
    grid[0][1] = b;
    grid[1][0] = b;
    grid[1][1] = a;
    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 12);
    vector<string> grid;

    if (mode == 0) {
        grid.assign(n, string(m, '.'));
    } else if (mode == 1) {
        int cardCount = rnd.next(1, min(12, (int)LABELS.size()));
        grid = layeredRectangles(n, m, cardCount);
    } else if (mode == 2) {
        n = rnd.next(2, 9);
        m = rnd.next(2, 9);
        grid = nestedRectangles(n, m);
    } else if (mode == 3) {
        int cardCount = rnd.next(1, min(20, (int)LABELS.size()));
        grid = layeredRectangles(n, m, cardCount);
        int dots = rnd.next(1, max(1, n * m / 4));
        for (int i = 0; i < dots; ++i) {
            grid[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '.';
        }
    } else if (mode == 4) {
        grid = invalidHole(n, m);
    } else {
        grid = invalidCycle();
    }

    printGrid(grid);
    return 0;
}
