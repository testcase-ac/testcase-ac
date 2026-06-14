#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Cell = pair<int, int>;

Cell randomCell(int lo, int hi) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

Cell uniqueCell(set<Cell>& used, int lo, int hi) {
    while (true) {
        Cell cell = randomCell(lo, hi);
        if (used.insert(cell).second) return cell;
    }
}

void addRectangleParity(vector<Cell>& cells, set<Cell>& used, int lo, int hi) {
    int x1 = rnd.next(lo, hi);
    int x2 = rnd.next(lo, hi);
    while (x2 == x1) x2 = rnd.next(lo, hi);
    int y1 = rnd.next(lo, hi);
    int y2 = rnd.next(lo, hi);
    while (y2 == y1) y2 = rnd.next(lo, hi);

    vector<Cell> rect = {{x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}};
    for (Cell cell : rect) {
        if (used.insert(cell).second) {
            cells.push_back(cell);
        } else {
            cells.erase(find(cells.begin(), cells.end(), cell));
            used.erase(cell);
        }
    }
}

void printCase(vector<Cell> current, vector<Cell> target) {
    shuffle(current.begin(), current.end());
    shuffle(target.begin(), target.end());

    println(static_cast<int>(current.size()), static_cast<int>(target.size()));
    for (Cell cell : current) println(cell.first, cell.second);
    for (Cell cell : target) println(cell.first, cell.second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int lo = rnd.next(0, 4) == 0 ? 99990 : 1;
    int hi = lo == 1 ? rnd.next(4, 25) : 100000;

    vector<Cell> current;
    vector<Cell> target;
    set<Cell> currentUsed;
    set<Cell> targetUsed;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            Cell cell = uniqueCell(currentUsed, lo, hi);
            current.push_back(cell);
            target.push_back(cell);
            targetUsed.insert(cell);
        }
    } else if (mode == 1) {
        int n = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) current.push_back(uniqueCell(currentUsed, lo, hi));
        target.push_back(uniqueCell(targetUsed, lo, hi));
        int rectangles = rnd.next(1, 3);
        for (int i = 0; i < rectangles; ++i) addRectangleParity(target, targetUsed, lo, hi);
    } else if (mode == 2) {
        current.push_back(uniqueCell(currentUsed, lo, hi));
        target.push_back(uniqueCell(targetUsed, lo, hi));
        target.push_back(uniqueCell(targetUsed, lo, hi));
        if (rnd.next(0, 1)) current.push_back(uniqueCell(currentUsed, lo, hi));
    } else if (mode == 3) {
        current = {{1, 1}, {100000, 100000}};
        target = {{1, 100000}, {100000, 1}};
    } else {
        int n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) current.push_back(uniqueCell(currentUsed, lo, hi));
        int m = rnd.next(2, 10);
        for (int i = 0; i < m; ++i) target.push_back(uniqueCell(targetUsed, lo, hi));
    }

    printCase(current, target);
    return 0;
}
