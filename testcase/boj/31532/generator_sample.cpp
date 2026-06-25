#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int boundedY(long long value) {
    if (value < -1000000) return -1000000;
    if (value > 1000000) return 1000000;
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int b;
    vector<pair<int, int>> points;

    if (mode == 0) {
        n = 1;
        b = rnd.next(-1000000, 1000000);
        points.push_back({rnd.next(1, 1000000), rnd.next(-1000000, 1000000)});
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        b = rnd.next(-20, 20);
        int x = rnd.next(1, 20);
        int y = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            int dy = rnd.next(0, 3) == 0 ? rnd.next(-3, 3) : 0;
            points.push_back({x, boundedY(y + dy)});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        b = rnd.next(-30, 30);
        int slope = rnd.next(-10, 10);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1, 100);
            int noise = rnd.next(-5, 5);
            points.push_back({x, boundedY(1LL * slope * x + b + noise)});
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        b = rnd.any(vector<int>{-1000000, 0, 1000000});
        for (int i = 0; i < n; ++i) {
            int x = rnd.any(vector<int>{1, rnd.next(1, 1000000), 1000000});
            int y = rnd.any(vector<int>{-1000000, rnd.next(-1000000, 1000000), 1000000});
            points.push_back({x, y});
        }
    } else if (mode == 4) {
        n = rnd.next(3, 25);
        b = 0;
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1, 50);
            int y = rnd.next(0, 1) ? x : 0;
            points.push_back({x, y});
        }
    } else {
        n = rnd.next(2, 30);
        b = rnd.next(-1000000, 1000000);
        int maxX = rnd.next(1, 1000000);
        int lowY = rnd.next(-1000000, 1000000);
        int highY = rnd.next(lowY, 1000000);
        for (int i = 0; i < n; ++i) {
            points.push_back({rnd.next(1, maxX), rnd.next(lowY, highY)});
        }
    }

    shuffle(points.begin(), points.end());

    println(n, b);
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
