#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

int cross(const Point& a, const Point& b, const Point& c) {
    int ux = b.first - a.first;
    int uy = b.second - a.second;
    int vx = c.first - b.first;
    int vy = c.second - b.second;
    return ux * vy - uy * vx;
}

void compressCollinear(vector<Point>& points) {
    bool changed = true;
    while (changed && points.size() > 2) {
        changed = false;
        vector<Point> next;
        int n = (int)points.size();
        for (int i = 0; i < n; ++i) {
            const Point& prev = points[(i + n - 1) % n];
            const Point& cur = points[i];
            const Point& after = points[(i + 1) % n];
            if (cross(prev, cur, after) == 0) {
                changed = true;
                continue;
            }
            next.push_back(cur);
        }
        points = next;
    }
}

vector<Point> makeHistogramFence() {
    int columns = rnd.next(1, 6);
    vector<int> xs(columns + 1, 0);
    for (int i = 0; i < columns; ++i) {
        xs[i + 1] = xs[i] + rnd.next(1, 3);
    }

    vector<int> height(columns);
    bool hasStep = false;
    for (int i = 0; i < columns; ++i) {
        height[i] = rnd.next(1, 6);
        if (i > 0 && height[i] != height[i - 1]) {
            hasStep = true;
        }
    }
    if (columns > 1 && !hasStep) {
        height[rnd.next(columns)] = height[0] == 6 ? 5 : height[0] + 1;
    }

    vector<Point> points;
    points.push_back({0, 0});
    points.push_back({xs[columns], 0});
    points.push_back({xs[columns], height[columns - 1]});

    for (int i = columns - 1; i >= 1; --i) {
        points.push_back({xs[i], height[i]});
        points.push_back({xs[i], height[i - 1]});
    }
    points.push_back({0, height[0]});

    compressCollinear(points);
    return points;
}

void transformFence(vector<Point>& points) {
    bool transpose = rnd.next(0, 1) == 1;
    bool mirrorX = rnd.next(0, 1) == 1;
    bool mirrorY = rnd.next(0, 1) == 1;

    for (Point& p : points) {
        if (transpose) {
            swap(p.first, p.second);
        }
    }

    int maxX = 0;
    int maxY = 0;
    for (const Point& p : points) {
        maxX = max(maxX, p.first);
        maxY = max(maxY, p.second);
    }

    for (Point& p : points) {
        if (mirrorX) {
            p.first = maxX - p.first;
        }
        if (mirrorY) {
            p.second = maxY - p.second;
        }
    }

    int shiftX = rnd.next(0, 10000 - maxX);
    int shiftY = rnd.next(0, 10000 - maxY);
    for (Point& p : points) {
        p.first += shiftX;
        p.second += shiftY;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int blocks = rnd.next(1, 4);
    for (int block = 0; block < blocks; ++block) {
        vector<Point> points = makeHistogramFence();
        transformFence(points);
        shuffle(points.begin(), points.end());

        println((int)points.size());
        for (const Point& p : points) {
            println(p.first, p.second);
        }
        printf("\n");
    }

    println(0);
    return 0;
}
