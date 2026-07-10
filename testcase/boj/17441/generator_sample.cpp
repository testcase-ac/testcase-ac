#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

// Builds star-shaped polygons from integer rays whose angular gaps stay below pi.
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<Point> directions = {
        {1, 0}, {3, 1}, {2, 1}, {1, 1}, {1, 2}, {1, 3},
        {0, 1}, {-1, 3}, {-1, 2}, {-1, 1}, {-2, 1}, {-3, 1},
        {-1, 0}, {-3, -1}, {-2, -1}, {-1, -1}, {-1, -2}, {-1, -3},
        {0, -1}, {1, -3}, {1, -2}, {1, -1}, {2, -1}, {3, -1},
    };

    int mode = rnd.next(0, 7);
    vector<int> chosen;
    if (mode == 0) {
        chosen = {0, 6, 15};
    } else if (mode == 1) {
        chosen = {0, 6, 12, 18};
    } else if (mode == 2) {
        for (int i = 0; i < static_cast<int>(directions.size()); ++i) {
            chosen.push_back(i);
        }
    } else if (mode == 4) {
        chosen = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};
    } else if (mode == 6) {
        chosen = {0, 3, 6, 9, 12, 15, 18, 21};
    } else {
        for (int i = 0; i < static_cast<int>(directions.size()); ++i) {
            if (i % 6 == 0 || rnd.next(0, 99) < 45) {
                chosen.push_back(i);
            }
        }
    }

    int xScale = mode == 6 ? 3 : rnd.next(1, 2);
    int yScale = mode == 6 ? 1 : rnd.next(1, 2);
    vector<Point> polygon;
    polygon.reserve(chosen.size());
    for (int i = 0; i < static_cast<int>(chosen.size()); ++i) {
        int radius;
        if (mode == 0) {
            radius = rnd.next(1, 20);
        } else if (mode == 2 || mode == 4) {
            radius = i % 2 == 0 ? rnd.next(20, 70) : rnd.next(120, 300);
        } else if (mode == 5) {
            radius = rnd.next(500, 1400);
        } else if (mode == 6) {
            radius = rnd.next(30, 600);
        } else {
            radius = rnd.next(2, 250);
        }

        const Point& direction = directions[chosen[i]];
        polygon.push_back({direction.x * radius * xScale,
                           direction.y * radius * yScale});
    }

    int minX = polygon.front().x;
    int maxX = polygon.front().x;
    int minY = polygon.front().y;
    int maxY = polygon.front().y;
    for (const Point& point : polygon) {
        minX = min(minX, point.x);
        maxX = max(maxX, point.x);
        minY = min(minY, point.y);
        maxY = max(maxY, point.y);
    }

    int minTranslateX = -10000 - minX;
    int maxTranslateX = 10000 - maxX;
    int minTranslateY = -10000 - minY;
    int maxTranslateY = 10000 - maxY;
    int translateX = mode == 5
        ? (rnd.next(0, 1) == 0 ? minTranslateX : maxTranslateX)
        : rnd.next(minTranslateX, maxTranslateX);
    int translateY = mode == 5
        ? (rnd.next(0, 1) == 0 ? minTranslateY : maxTranslateY)
        : rnd.next(minTranslateY, maxTranslateY);

    println(polygon.size());
    for (const Point& point : polygon) {
        println(point.x + translateX, point.y + translateY);
    }
}
