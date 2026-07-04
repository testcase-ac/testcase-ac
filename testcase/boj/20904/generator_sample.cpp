#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Domino {
    int x1;
    int y1;
    int x2;
    int y2;
};

static void addDomino(vector<Domino>& dominoes, int x1, int y1, int x2, int y2) {
    dominoes.push_back({x1, y1, x2, y2});
}

static void randomizeOutput(vector<Domino>& dominoes) {
    shuffle(dominoes.begin(), dominoes.end());
    for (Domino& domino : dominoes) {
        if (rnd.next(0, 1) == 1) {
            swap(domino.x1, domino.x2);
            swap(domino.y1, domino.y2);
        }
    }
}

static vector<Domino> makeStrip() {
    vector<Domino> dominoes;
    int n = rnd.next(2, 18);
    int x = rnd.next(1, 10000 - 2 * n + 1);
    int y = rnd.next(1, 10000);

    for (int i = 0; i < n; ++i) {
        addDomino(dominoes, x + 2 * i, y, x + 2 * i + 1, y);
    }
    return dominoes;
}

static vector<Domino> makeCornerPairs() {
    vector<Domino> dominoes;
    int pairs = rnd.next(1, 8);
    int x = rnd.next(1, 10000 - 3 * pairs);
    int y = rnd.next(1, 9999);

    for (int i = 0; i < pairs; ++i) {
        int baseX = x + 3 * i;
        if (rnd.next(0, 1) == 0) {
            addDomino(dominoes, baseX, y, baseX, y + 1);
            addDomino(dominoes, baseX + 1, y, baseX + 2, y);
        } else {
            addDomino(dominoes, baseX, y, baseX + 1, y);
            addDomino(dominoes, baseX + 2, y, baseX + 2, y + 1);
        }
    }
    return dominoes;
}

static vector<Domino> makeDisconnectedBlocks() {
    vector<Domino> dominoes;
    int blocks = rnd.next(2, 5);
    int startX = rnd.next(1, 9000);
    int startY = rnd.next(1, 9000);

    for (int block = 0; block < blocks; ++block) {
        int x = startX + block * rnd.next(20, 80);
        int y = startY + block * rnd.next(20, 80);
        int count = rnd.next(1, 4);
        for (int i = 0; i < count; ++i) {
            if (rnd.next(0, 1) == 0) {
                addDomino(dominoes, x + 2 * i, y, x + 2 * i + 1, y);
            } else {
                addDomino(dominoes, x, y + 2 * i, x, y + 2 * i + 1);
            }
        }
    }
    return dominoes;
}

static vector<Domino> makeRectangleTiling() {
    vector<Domino> dominoes;
    int rows = rnd.next(2, 6);
    int cols = rnd.next(2, 8);
    if ((rows * cols) % 2 == 1) ++cols;

    int x = rnd.next(1, 10000 - cols + 1);
    int y = rnd.next(1, 10000 - rows + 1);
    bool horizontal = rnd.next(0, 1) == 1;

    if (horizontal) {
        if (cols % 2 == 1) ++cols;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; c += 2) {
                addDomino(dominoes, x + c, y + r, x + c + 1, y + r);
            }
        }
    } else {
        if (rows % 2 == 1) ++rows;
        for (int r = 0; r < rows; r += 2) {
            for (int c = 0; c < cols; ++c) {
                addDomino(dominoes, x + c, y + r, x + c, y + r + 1);
            }
        }
    }
    return dominoes;
}

static vector<Domino> makeUpperBoundary() {
    vector<Domino> dominoes;
    int n = rnd.next(2, 10);
    int x = 10000 - 2 * n + 1;
    int y = rnd.any(vector<int>{1, 9999, 10000});

    for (int i = 0; i < n; ++i) {
        if (y == 10000) {
            addDomino(dominoes, x + 2 * i, y, x + 2 * i + 1, y);
        } else {
            addDomino(dominoes, 10000 - i, y, 10000 - i, y + 1);
        }
    }
    return dominoes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<Domino> dominoes;

    if (mode == 0) {
        dominoes = makeStrip();
    } else if (mode == 1) {
        dominoes = makeCornerPairs();
    } else if (mode == 2) {
        dominoes = makeDisconnectedBlocks();
    } else if (mode == 3) {
        dominoes = makeRectangleTiling();
    } else {
        dominoes = makeUpperBoundary();
    }

    randomizeOutput(dominoes);
    println((int)dominoes.size());
    for (const Domino& domino : dominoes) {
        println(domino.x1, domino.y1, domino.x2, domino.y2);
    }

    return 0;
}
