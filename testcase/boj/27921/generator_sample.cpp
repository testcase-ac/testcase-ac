#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

vector<string> makeGrid(int h, int w, const vector<Cell>& cells) {
    vector<string> grid(h, string(w, '.'));
    for (auto [r, c] : cells) {
        grid[r][c] = 'O';
    }
    return grid;
}

vector<Cell> randomCells(int h, int w, int k) {
    vector<Cell> cells;
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            cells.emplace_back(r, c);
        }
    }
    shuffle(cells.begin(), cells.end());
    cells.resize(k);
    return cells;
}

vector<Cell> lineCells(int h, int w, int k) {
    vector<Cell> candidates;
    int mode = rnd.next(4);
    if (mode == 0) {
        int r = rnd.next(h);
        for (int c = 0; c < w; ++c) {
            candidates.emplace_back(r, c);
        }
    } else if (mode == 1) {
        int c = rnd.next(w);
        for (int r = 0; r < h; ++r) {
            candidates.emplace_back(r, c);
        }
    } else if (mode == 2) {
        int start = rnd.next(-w + 1, h - 1);
        for (int r = 0; r < h; ++r) {
            int c = r - start;
            if (0 <= c && c < w) {
                candidates.emplace_back(r, c);
            }
        }
    } else {
        int start = rnd.next(0, h + w - 2);
        for (int r = 0; r < h; ++r) {
            int c = start - r;
            if (0 <= c && c < w) {
                candidates.emplace_back(r, c);
            }
        }
    }

    set<Cell> chosen;
    shuffle(candidates.begin(), candidates.end());
    for (Cell cell : candidates) {
        if ((int)chosen.size() == k) {
            break;
        }
        chosen.insert(cell);
    }
    while ((int)chosen.size() < k) {
        chosen.insert({rnd.next(h), rnd.next(w)});
    }
    return vector<Cell>(chosen.begin(), chosen.end());
}

vector<Cell> clusterCells(int h, int w, int k) {
    int blockH = rnd.next(1, h);
    int blockW = rnd.next(1, w);
    while (blockH * blockW < k) {
        blockH = rnd.next(1, h);
        blockW = rnd.next(1, w);
    }
    int top = rnd.next(0, h - blockH);
    int left = rnd.next(0, w - blockW);

    vector<Cell> cells;
    for (int r = 0; r < blockH; ++r) {
        for (int c = 0; c < blockW; ++c) {
            cells.emplace_back(top + r, left + c);
        }
    }
    shuffle(cells.begin(), cells.end());
    cells.resize(k);
    return cells;
}

void printCase(int h1, int w1, const vector<Cell>& first, int h2, int w2, const vector<Cell>& second) {
    println(h1, w1);
    for (const string& row : makeGrid(h1, w1, first)) {
        println(row);
    }
    println(h2, w2);
    for (const string& row : makeGrid(h2, w2, second)) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int h1 = rnd.next(1, 10);
    int w1 = rnd.next(1, 10);
    int h2 = rnd.next(1, 10);
    int w2 = rnd.next(1, 10);
    int maxCoins = min(h1 * w1, h2 * w2);
    int k = rnd.next(1, maxCoins);

    vector<Cell> first;
    vector<Cell> second;

    if (mode == 0) {
        k = 1;
        first = randomCells(h1, w1, k);
        second = randomCells(h2, w2, k);
    } else if (mode == 1) {
        int shapeH = rnd.next(1, min(h1, h2));
        int shapeW = rnd.next(1, min(w1, w2));
        k = rnd.next(1, shapeH * shapeW);
        vector<Cell> shape = randomCells(shapeH, shapeW, k);

        int top1 = rnd.next(0, h1 - shapeH);
        int left1 = rnd.next(0, w1 - shapeW);
        int top2 = rnd.next(0, h2 - shapeH);
        int left2 = rnd.next(0, w2 - shapeW);
        for (auto [r, c] : shape) {
            first.emplace_back(top1 + r, left1 + c);
            second.emplace_back(top2 + r, left2 + c);
        }
    } else if (mode == 2) {
        k = rnd.next(max(1, maxCoins / 2), maxCoins);
        first = randomCells(h1, w1, k);
        second = randomCells(h2, w2, k);
    } else if (mode == 3) {
        k = rnd.next(1, min(maxCoins, max(h1 + w1, h2 + w2)));
        first = lineCells(h1, w1, k);
        second = lineCells(h2, w2, k);
    } else {
        first = clusterCells(h1, w1, k);
        second = clusterCells(h2, w2, k);
    }

    printCase(h1, w1, first, h2, w2, second);
    return 0;
}
