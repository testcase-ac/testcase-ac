#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MAX_COORD = 1000000;

int oddCoord(int value) {
    if (value < 1) value = 1;
    if (value > MAX_COORD - 1) value = MAX_COORD - 1;
    if (value % 2 == 0) --value;
    return value;
}

bool addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int x, int y) {
    x = oddCoord(x);
    y = oddCoord(y);
    if (!used.insert({x, y}).second) return false;
    points.push_back({x, y});
    return true;
}

void addRandomPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used) {
    while (true) {
        int x = 2 * rnd.next(0, 499999) + 1;
        int y = 2 * rnd.next(0, 499999) + 1;
        if (addPoint(points, used, x, y)) return;
    }
}

void fillToSize(vector<pair<int, int>>& points, set<pair<int, int>>& used, int n) {
    while ((int)points.size() < n) addRandomPoint(points, used);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(1, 8);
        fillToSize(points, used, n);
    } else if (mode == 1) {
        int rows = rnd.next(2, 6);
        int cols = rnd.next(2, 6);
        n = rnd.next(rows + cols - 1, rows * cols);
        int baseX = 2 * rnd.next(0, 40) + 1;
        int baseY = 2 * rnd.next(0, 40) + 1;
        vector<pair<int, int>> candidates;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                candidates.push_back({baseX + 2 * j, baseY + 2 * i});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < n; ++i) addPoint(points, used, candidates[i].first, candidates[i].second);
    } else if (mode == 2) {
        n = rnd.next(8, 24);
        int centerX = 2 * rnd.next(10, 200) + 1;
        int centerY = 2 * rnd.next(10, 200) + 1;
        for (int dx : {-5, -3, -1, 1, 3, 5}) {
            for (int dy : {-5, -3, -1, 1, 3, 5}) {
                if (rnd.next(0, 1)) addPoint(points, used, centerX + dx, centerY + dy);
            }
        }
        fillToSize(points, used, n);
    } else if (mode == 3) {
        n = rnd.next(8, 28);
        int sharedX = 2 * rnd.next(0, 120) + 1;
        int sharedY = 2 * rnd.next(0, 120) + 1;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                addPoint(points, used, sharedX, 2 * rnd.next(0, 200) + 1);
            } else {
                addPoint(points, used, 2 * rnd.next(0, 200) + 1, sharedY);
            }
        }
        fillToSize(points, used, n);
    } else if (mode == 4) {
        n = rnd.next(10, 30);
        int stepX = 2 * rnd.next(1, 15);
        int stepY = 2 * rnd.next(1, 15);
        int startX = 2 * rnd.next(0, 50) + 1;
        int startY = 2 * rnd.next(0, 50) + 1;
        for (int i = 0; i < n; ++i) {
            int wobble = 2 * rnd.next(-2, 2);
            addPoint(points, used, startX + i * stepX, startY + i * stepY + wobble);
        }
        fillToSize(points, used, n);
    } else if (mode == 5) {
        n = rnd.next(6, 20);
        vector<int> xs = {1, 3, 5, 999995, 999997, 999999};
        vector<int> ys = {1, 3, 5, 999995, 999997, 999999};
        shuffle(xs.begin(), xs.end());
        shuffle(ys.begin(), ys.end());
        for (int x : xs) {
            for (int y : ys) {
                if ((int)points.size() < n && rnd.next(0, 1)) addPoint(points, used, x, y);
            }
        }
        fillToSize(points, used, n);
    } else {
        n = rnd.next(16, 36);
        vector<pair<int, int>> centers = {
            {101, 101},
            {101, 301},
            {301, 101},
            {301, 301},
        };
        for (auto [cx, cy] : centers) {
            int take = rnd.next(2, 7);
            for (int i = 0; i < take; ++i) {
                addPoint(points, used, cx + 2 * rnd.next(-5, 5), cy + 2 * rnd.next(-5, 5));
            }
        }
        fillToSize(points, used, n);
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (auto [x, y] : points) println(x, y);

    return 0;
}
