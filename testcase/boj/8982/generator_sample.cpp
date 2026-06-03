#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Segment {
    int left;
    int right;
    int y;
};

int differentY(int previous, int low, int high) {
    int y = rnd.next(low, high);
    if (y == previous) {
        y = (y == high ? low : y + 1);
    }
    return y;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int horizontalCount;
    if (mode == 0) {
        horizontalCount = 1;
    } else if (mode == 1) {
        horizontalCount = rnd.next(2, 4);
    } else {
        horizontalCount = rnd.next(3, 12);
    }

    int maxY = rnd.next(3, mode == 5 ? 40 : 12);
    vector<int> y(horizontalCount);

    if (mode == 0) {
        y[0] = rnd.next(1, maxY);
    } else if (mode == 1) {
        int base = rnd.next(1, maxY);
        for (int i = 0; i < horizontalCount; ++i) {
            y[i] = min(maxY, base + i);
            if (i > 0 && y[i] == y[i - 1]) y[i] = y[i - 1] - 1;
        }
    } else if (mode == 2) {
        int base = rnd.next(horizontalCount, maxY + horizontalCount);
        for (int i = 0; i < horizontalCount; ++i) {
            y[i] = max(1, min(maxY, base - i));
            if (i > 0 && y[i] == y[i - 1]) y[i] = min(maxY, y[i - 1] + 1);
        }
    } else if (mode == 3) {
        int center = rnd.next(0, horizontalCount - 1);
        for (int i = 0; i < horizontalCount; ++i) {
            y[i] = 1 + abs(i - center) + rnd.next(0, 2);
            y[i] = min(y[i], maxY);
            if (i > 0 && y[i] == y[i - 1]) y[i] = differentY(y[i - 1], 1, maxY);
        }
    } else {
        y[0] = rnd.next(1, maxY);
        for (int i = 1; i < horizontalCount; ++i) {
            y[i] = differentY(y[i - 1], 1, maxY);
        }
    }
    for (int i = 1; i < horizontalCount; ++i) {
        if (y[i] == y[i - 1]) y[i] = differentY(y[i - 1], 1, maxY);
    }

    vector<Segment> segments;
    vector<pair<int, int>> vertices;
    int x = 0;
    vertices.push_back({0, 0});
    vertices.push_back({0, y[0]});
    for (int i = 0; i < horizontalCount; ++i) {
        int width = rnd.next(1, mode == 5 ? 25 : 8);
        int nextX = x + width;
        segments.push_back({x, nextX, y[i]});
        vertices.push_back({nextX, y[i]});
        if (i + 1 < horizontalCount) {
            vertices.push_back({nextX, y[i + 1]});
        }
        x = nextX;
    }
    vertices.push_back({x, 0});

    vector<int> order(horizontalCount);
    for (int i = 0; i < horizontalCount; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    int k;
    if (horizontalCount == 1) {
        k = 1;
    } else if (mode == 4) {
        k = horizontalCount;
    } else {
        k = rnd.next(1, horizontalCount);
    }
    order.resize(k);
    sort(order.begin(), order.end());

    println(static_cast<int>(vertices.size()));
    for (auto [vx, vy] : vertices) {
        println(vx, vy);
    }
    println(k);
    for (int index : order) {
        const Segment& segment = segments[index];
        println(segment.left, segment.y, segment.right, segment.y);
    }

    return 0;
}
