#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<int, int>;

static vector<Point> allCells(int n) {
    vector<Point> cells;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            cells.push_back({r, c});
        }
    }
    return cells;
}

static void addCell(vector<Point>& legions, Point p, Point start, int n, int limit) {
    if (p.first < 0 || p.first >= n || p.second < 0 || p.second >= n ||
        p == start || static_cast<int>(legions.size()) >= limit) {
        return;
    }
    if (find(legions.begin(), legions.end(), p) == legions.end()) {
        legions.push_back(p);
    }
}

static void fillRandom(vector<Point>& legions, const vector<Point>& candidates, Point start, int n, int target) {
    vector<Point> shuffled = candidates;
    shuffle(shuffled.begin(), shuffled.end());
    for (Point p : shuffled) {
        addCell(legions, p, start, n, target);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 5) {
        n = rnd.any(vector<int>{20, 30, 50, 100});
    } else {
        n = rnd.next(2, 12);
    }

    Point start = {rnd.next(0, n - 1), rnd.next(0, n - 1)};
    int legionTarget = mode == 0 ? 0 : rnd.next(1, min(10, n * n - 1));
    vector<Point> legions;
    vector<Point> candidates = allCells(n);

    if (mode == 1) {
        vector<Point> diagonal;
        for (Point p : candidates) {
            if (p != start && ((p.first + p.second) & 1) == ((start.first + start.second) & 1)) {
                diagonal.push_back(p);
            }
        }
        fillRandom(legions, diagonal, start, n, legionTarget);
    } else if (mode == 2) {
        for (int d = 1; d < n && static_cast<int>(legions.size()) < legionTarget; ++d) {
            addCell(legions, {start.first - d, start.second - d}, start, n, legionTarget);
            addCell(legions, {start.first - d, start.second + d}, start, n, legionTarget);
            addCell(legions, {start.first + d, start.second - d}, start, n, legionTarget);
            addCell(legions, {start.first + d, start.second + d}, start, n, legionTarget);
        }
        vector<Point> sameParity;
        for (Point p : candidates) {
            if (((p.first + p.second) & 1) == ((start.first + start.second) & 1)) {
                sameParity.push_back(p);
            }
        }
        fillRandom(legions, sameParity, start, n, legionTarget);
    } else if (mode == 3) {
        vector<Point> oppositeParity;
        for (Point p : candidates) {
            if (p != start && ((p.first + p.second) & 1) != ((start.first + start.second) & 1)) {
                oppositeParity.push_back(p);
            }
        }
        fillRandom(legions, oppositeParity, start, n, min(legionTarget, rnd.next(1, min(3, legionTarget))));
        fillRandom(legions, candidates, start, n, legionTarget);
    } else if (mode == 4) {
        vector<Point> edgeCells;
        for (Point p : candidates) {
            if (p.first == 0 || p.second == 0 || p.first == n - 1 || p.second == n - 1) {
                edgeCells.push_back(p);
            }
        }
        addCell(legions, {0, 0}, start, n, legionTarget);
        addCell(legions, {0, n - 1}, start, n, legionTarget);
        addCell(legions, {n - 1, 0}, start, n, legionTarget);
        addCell(legions, {n - 1, n - 1}, start, n, legionTarget);
        fillRandom(legions, edgeCells, start, n, legionTarget);
    } else if (mode == 5) {
        int sameParityTarget = rnd.next(0, legionTarget);
        vector<Point> sameParity;
        vector<Point> oppositeParity;
        for (Point p : candidates) {
            if (p == start) {
                continue;
            }
            if (((p.first + p.second) & 1) == ((start.first + start.second) & 1)) {
                sameParity.push_back(p);
            } else {
                oppositeParity.push_back(p);
            }
        }
        fillRandom(legions, sameParity, start, n, sameParityTarget);
        fillRandom(legions, oppositeParity, start, n, legionTarget);
    }

    vector<vector<int>> grid(n, vector<int>(n, 0));
    grid[start.first][start.second] = 2;
    for (Point p : legions) {
        if (p.first >= 0 && p.first < n && p.second >= 0 && p.second < n) {
            grid[p.first][p.second] = 1;
        }
    }

    println(n);
    for (int r = 0; r < n; ++r) {
        println(grid[r]);
    }

    return 0;
}
