#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

void addPoint(vector<Point>& points, set<Point>& used, Point point) {
    if (used.insert(point).second) {
        points.push_back(point);
    }
}

Point randomUnusedPoint(int n, const set<Point>& used) {
    while (true) {
        Point point = {rnd.next(0, n - 1), rnd.next(0, n - 1)};
        if (!used.count(point)) return point;
    }
}

vector<Point> knightNeighbors(Point p, int n) {
    const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    vector<Point> result;
    for (int k = 0; k < 8; ++k) {
        int x = p.first + dx[k];
        int y = p.second + dy[k];
        if (0 <= x && x < n && 0 <= y && y < n) {
            result.push_back({x, y});
        }
    }
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 3;
    } else if (mode <= 3) {
        n = rnd.next(4, 10);
    } else {
        n = rnd.next(11, 20);
    }

    vector<int> costs;
    int costMode = rnd.next(0, 4);
    if (costMode == 0) {
        costs = {rnd.next(1, 3), rnd.next(1, 3), rnd.next(1, 3)};
    } else if (costMode == 1) {
        costs = {1, rnd.next(20, 50), rnd.next(20, 50)};
    } else if (costMode == 2) {
        costs = {rnd.next(20, 50), 1, rnd.next(20, 50)};
    } else if (costMode == 3) {
        costs = {rnd.next(20, 50), rnd.next(20, 50), 1};
    } else {
        costs = {rnd.next(1, 50), rnd.next(1, 50), rnd.next(1, 50)};
    }

    vector<Point> points;
    set<Point> used;

    if (mode == 0) {
        addPoint(points, used, {rnd.next(0, 2), rnd.next(0, 2)});
        vector<Point> corners = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
        shuffle(corners.begin(), corners.end());
        for (Point point : corners) addPoint(points, used, point);
    } else if (mode == 1) {
        int row = rnd.next(0, n - 1);
        addPoint(points, used, {row, rnd.next(0, n - 1)});
        vector<int> cols(n);
        for (int i = 0; i < n; ++i) cols[i] = i;
        shuffle(cols.begin(), cols.end());
        for (int col : cols) addPoint(points, used, {row, col});
    } else if (mode == 2) {
        int base = rnd.next(0, n - 1);
        addPoint(points, used, {base, base});
        vector<Point> diagonal;
        for (int i = 0; i < n; ++i) diagonal.push_back({i, i});
        for (int i = 0; i < n; ++i) diagonal.push_back({i, n - 1 - i});
        shuffle(diagonal.begin(), diagonal.end());
        for (Point point : diagonal) addPoint(points, used, point);
    } else if (mode == 3) {
        Point start = {rnd.next(1, n - 2), rnd.next(1, n - 2)};
        addPoint(points, used, start);
        for (Point point : knightNeighbors(start, n)) addPoint(points, used, point);
    } else if (mode == 4) {
        Point center = {rnd.next(1, n - 2), rnd.next(1, n - 2)};
        addPoint(points, used, center);
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                addPoint(points, used, {center.first + dx, center.second + dy});
            }
        }
    } else {
        addPoint(points, used, randomUnusedPoint(n, used));
    }

    int m = rnd.next(1, 4);
    while ((int)points.size() < m + 1) {
        addPoint(points, used, randomUnusedPoint(n, used));
    }

    Point start = points[0];
    vector<Point> foods(points.begin() + 1, points.end());
    shuffle(foods.begin(), foods.end());
    foods.resize(m);

    println(n);
    println(costs);
    println(start.first, start.second);
    println(m);
    for (Point food : foods) {
        println(food.first, food.second);
    }

    return 0;
}
