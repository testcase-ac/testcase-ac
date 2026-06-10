#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
    } else if (mode == 2) {
        n = rnd.next(5, 10);
    } else if (mode == 3) {
        n = rnd.next(11, 25);
    } else {
        n = rnd.next(26, 60);
    }

    int total = 3 * n;
    int step = rnd.next(1, 5);
    int span = (total - 1) * step;
    int start = rnd.next(-900, 900 - span);

    vector<pair<int, int>> points;
    points.reserve(total);
    for (int i = 0; i < total; ++i) {
        int x = start + i * step;
        int y = x * x;
        points.push_back({x, y});
    }

    bool swapAxes = rnd.next(0, 1);
    int sx = rnd.next(0, 1) ? 1 : -1;
    int sy = rnd.next(0, 1) ? 1 : -1;

    vector<pair<int, int>> transformed;
    transformed.reserve(total);
    int minX = 1000000000, maxX = -1000000000;
    int minY = 1000000000, maxY = -1000000000;
    for (auto [x, y] : points) {
        if (swapAxes) {
            std::swap(x, y);
        }
        x *= sx;
        y *= sy;
        transformed.push_back({x, y});
        minX = min(minX, x);
        maxX = max(maxX, x);
        minY = min(minY, y);
        maxY = max(maxY, y);
    }

    int shiftX = rnd.next(-1000000 - minX, 1000000 - maxX);
    int shiftY = rnd.next(-1000000 - minY, 1000000 - maxY);
    for (auto& [x, y] : transformed) {
        x += shiftX;
        y += shiftY;
    }

    shuffle(transformed.begin(), transformed.end());

    println(n);
    for (auto [x, y] : transformed) {
        println(x, y);
    }

    return 0;
}
