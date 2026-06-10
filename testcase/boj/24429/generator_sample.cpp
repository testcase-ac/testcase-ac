#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

vector<Point> allIntermediateCells(int n) {
    vector<Point> cells;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            if ((r == 1 && c == 1) || (r == n && c == n)) {
                continue;
            }
            cells.push_back({r, c});
        }
    }
    return cells;
}

void addUnique(vector<Point>& points, set<Point>& used, Point point) {
    if (used.insert(point).second) {
        points.push_back(point);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 4) ? rnd.next(5, 7) : rnd.next(5, 12);

    println(n);
    int valueMode = rnd.next(0, 3);
    for (int r = 1; r <= n; ++r) {
        vector<int> row;
        for (int c = 1; c <= n; ++c) {
            int value = 1;
            if (valueMode == 0) {
                value = rnd.next(1, 20);
            } else if (valueMode == 1) {
                value = r * 10 + c;
            } else if (valueMode == 2) {
                value = (r == c || r + c == n + 1) ? rnd.next(50000, 100000)
                                                   : rnd.next(1, 9);
            } else {
                value = rnd.next(99950, 100000);
            }
            row.push_back(value);
        }
        println(row);
    }

    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        int p = rnd.next(1, min(n + 3, n * n - 2));
        vector<Point> cells = allIntermediateCells(n);
        sort(cells.begin(), cells.end());
        shuffle(cells.begin(), cells.end());
        cells.resize(p);
        sort(cells.begin(), cells.end());
        points = cells;
    } else if (mode == 1) {
        addUnique(points, used, {1, n});
        addUnique(points, used, {n, 1});
        int extra = rnd.next(0, min(5, n * n - 4));
        vector<Point> cells = allIntermediateCells(n);
        shuffle(cells.begin(), cells.end());
        for (Point cell : cells) {
            if ((int)points.size() >= extra + 2) {
                break;
            }
            addUnique(points, used, cell);
        }
    } else if (mode == 2) {
        int p = rnd.next(1, min(2 * n, n * n - 2));
        vector<Point> cells = allIntermediateCells(n);
        shuffle(cells.begin(), cells.end());
        cells.resize(p);
        points = cells;
    } else if (mode == 3) {
        int row = rnd.next(1, n - 1);
        int col = rnd.next(1, n);
        for (int c = 2; c <= n; ++c) {
            addUnique(points, used, {row, c});
        }
        for (int r = 2; r < n; ++r) {
            addUnique(points, used, {r, col});
        }
        shuffle(points.begin(), points.end());
        int p = rnd.next(1, (int)points.size());
        points.resize(p);
    } else if (mode == 4) {
        vector<Point> cells = allIntermediateCells(n);
        shuffle(cells.begin(), cells.end());
        int p = rnd.next(max(1, n * n - 2 - n), n * n - 2);
        cells.resize(p);
        points = cells;
    } else {
        int p = rnd.next(1, min(3 * n, n * n - 2));
        int r = 1;
        int c = 1;
        for (int i = 0; i < p; ++i) {
            if (r == n) {
                ++c;
            } else if (c == n) {
                ++r;
            } else if (rnd.next(0, 1) == 0) {
                ++r;
            } else {
                ++c;
            }
            if (r == n && c == n) {
                break;
            }
            points.push_back({r, c});
        }
        if (points.empty()) {
            points.push_back({1, 2});
        }
    }

    println((int)points.size());
    for (Point point : points) {
        println(point.first, point.second);
    }

    return 0;
}
