#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using Cell = pair<int, int>;

static vector<int> chooseCells(int total, int count) {
    vector<int> cells(total);
    iota(cells.begin(), cells.end(), 0);
    shuffle(cells.begin(), cells.end());
    cells.resize(count);
    return cells;
}

static vector<vector<int>> makeGrid(int h, int w, const vector<int>& cells) {
    vector<vector<int>> grid(h, vector<int>(w, 0));
    for (int id : cells) {
        grid[id / w][id % w] = 1;
    }
    return grid;
}

static void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int w = rnd.next(1, 12);
    int h = rnd.next(1, 12);
    if (mode == 0) {
        w = rnd.next(1, 4);
        h = rnd.next(1, 4);
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            h = 1;
            w = rnd.next(1, 15);
        } else {
            w = 1;
            h = rnd.next(1, 15);
        }
    }

    int total = w * h;
    int initialCount;
    int targetCount;

    if (mode == 2) {
        initialCount = rnd.next(0, total);
        targetCount = total == 0 ? 0 : rnd.next(0, total);
        if (total > 1 && initialCount == targetCount) {
            targetCount = (targetCount + 1) % (total + 1);
        }
    } else if (mode == 3) {
        initialCount = rnd.next(max(0, total - 5), total);
        targetCount = initialCount;
    } else if (mode == 4) {
        initialCount = rnd.next(0, min(total, 4));
        targetCount = initialCount;
    } else {
        initialCount = rnd.next(0, total);
        targetCount = initialCount;
    }

    vector<int> initialCells = chooseCells(total, initialCount);
    vector<int> targetCells;

    if (mode == 5 && w > 1 && h > 1 && initialCount > 0) {
        targetCells = initialCells;
        shuffle(targetCells.begin(), targetCells.end());
        int moves = rnd.next(1, min(initialCount, 6));
        for (int i = 0; i < moves; ++i) {
            int& id = targetCells[rnd.next(0, static_cast<int>(targetCells.size()) - 1)];
            int y = id / w;
            int x = id % w;
            vector<Cell> candidates;
            if (y > 0) candidates.emplace_back(y - 1, x);
            if (y + 1 < h) candidates.emplace_back(y + 1, x);
            if (x > 0) candidates.emplace_back(y, x - 1);
            if (x + 1 < w) candidates.emplace_back(y, x + 1);
            Cell next = rnd.any(candidates);
            id = next.first * w + next.second;
        }
        sort(targetCells.begin(), targetCells.end());
        targetCells.erase(unique(targetCells.begin(), targetCells.end()), targetCells.end());
        while (static_cast<int>(targetCells.size()) < targetCount) {
            int id = rnd.next(0, total - 1);
            if (find(targetCells.begin(), targetCells.end(), id) == targetCells.end()) {
                targetCells.push_back(id);
            }
        }
    } else {
        targetCells = chooseCells(total, targetCount);
    }

    println(w, h);
    printGrid(makeGrid(h, w, initialCells));
    printGrid(makeGrid(h, w, targetCells));

    return 0;
}
