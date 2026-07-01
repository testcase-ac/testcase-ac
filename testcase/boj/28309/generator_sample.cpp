#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

void addCell(vector<Cell>& cells, set<Cell>& used, int r, int c, int x, int y) {
    if (x < 1 || x > r || y < 1 || y > c) return;
    if ((x == 1 && y == 1) || (x == r && y == c)) return;
    if (used.insert({x, y}).second) cells.push_back({x, y});
}

Cell randomFreeCell(const vector<Cell>& pool, const set<Cell>& used) {
    vector<Cell> available;
    for (Cell cell : pool) {
        if (!used.count(cell)) available.push_back(cell);
    }
    return rnd.any(available);
}

void fillRandom(vector<Cell>& cells, set<Cell>& used, const vector<Cell>& pool, int target) {
    while ((int)cells.size() < target) {
        Cell cell = randomFreeCell(pool, used);
        used.insert(cell);
        cells.push_back(cell);
    }
}

vector<Cell> allCells(int r, int c) {
    vector<Cell> pool;
    for (int x = 1; x <= r; ++x) {
        for (int y = 1; y <= c; ++y) {
            if ((x == 1 && y == 1) || (x == r && y == c)) continue;
            pool.push_back({x, y});
        }
    }
    return pool;
}

void printCase(int r, int c, vector<Cell> cells) {
    shuffle(cells.begin(), cells.end());
    println(r, c, (int)cells.size());
    for (Cell cell : cells) println(cell.first, cell.second);
}

vector<Cell> makeCase(int mode, int& r, int& c) {
    vector<Cell> cells;
    set<Cell> used;

    if (mode == 0) {
        r = rnd.next(2, 6);
        c = rnd.next(2, 6);
        vector<Cell> pool = allCells(r, c);
        fillRandom(cells, used, pool, rnd.next(1, min(8, (int)pool.size())));
    } else if (mode == 1) {
        int len = rnd.next(2, 8);
        r = rnd.next(len + 1, len + 8);
        c = rnd.next(len + 1, len + 8);
        int x = rnd.next(1, 2);
        int y = rnd.next(2, 3);
        for (int i = 0; i < len; ++i) {
            addCell(cells, used, r, c, min(r, x + i), min(c, y + i));
        }
        vector<Cell> pool = allCells(r, c);
        fillRandom(cells, used, pool, rnd.next((int)cells.size(), min(12, (int)pool.size())));
    } else if (mode == 2) {
        int n = rnd.next(4, 12);
        r = rnd.next(n + 2, n + 12);
        c = rnd.next(n + 2, n + 12);
        int baseX = rnd.next(1, min(3, r - 1));
        int baseY = rnd.next(max(2, c - n - 2), c - 1);
        for (int i = 0; i < n; ++i) {
            addCell(cells, used, r, c, min(r, baseX + i), max(1, baseY - i));
        }
        vector<Cell> pool = allCells(r, c);
        fillRandom(cells, used, pool, n);
    } else if (mode == 3) {
        r = rnd.next(4, 12);
        c = rnd.next(4, 12);
        int n = rnd.next(3, min(12, r + c - 4));
        for (int y = 2; y <= c && (int)cells.size() < n / 2; ++y) {
            addCell(cells, used, r, c, 1, y);
        }
        for (int x = 2; x <= r && (int)cells.size() < n; ++x) {
            addCell(cells, used, r, c, x, c);
        }
        vector<Cell> pool = allCells(r, c);
        fillRandom(cells, used, pool, n);
    } else {
        r = rnd.next(999900, 1000000);
        c = rnd.next(999900, 1000000);
        int n = rnd.next(4, 12);
        addCell(cells, used, r, c, 1, rnd.next(2, min(c, 20)));
        addCell(cells, used, r, c, rnd.next(2, min(r, 20)), 1);
        addCell(cells, used, r, c, rnd.next(r - 20, r), rnd.next(c - 20, c - 1));
        addCell(cells, used, r, c, rnd.next(r / 2 - 10, r / 2 + 10), rnd.next(c / 2 - 10, c / 2 + 10));
        vector<Cell> pool;
        while ((int)pool.size() < 80) {
            Cell cell = {rnd.next(1, r), rnd.next(1, c)};
            if ((cell.first == 1 && cell.second == 1) || (cell.first == r && cell.second == c)) continue;
            if (used.count(cell)) continue;
            pool.push_back(cell);
        }
        fillRandom(cells, used, pool, n);
    }

    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int r = 0, c = 0;
        vector<Cell> cells = makeCase(tc == 0 ? rnd.next(5) : rnd.next(5), r, c);
        printCase(r, c, cells);
    }

    return 0;
}
