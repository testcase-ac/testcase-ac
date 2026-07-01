#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

pair<int, int> randomPoint(int limit) {
    int x = rnd.next(-limit, limit);
    int y = rnd.next(-limit, limit);
    if (x == 0 && y == 0) {
        if (rnd.next(2) == 0) x = rnd.next(2) == 0 ? -1 : 1;
        else y = rnd.next(2) == 0 ? -1 : 1;
    }
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int t = rnd.next(1, 50);
    vector<pair<int, int>> points;
    points.reserve(t);

    if (mode == 0) {
        for (int i = 0; i < t; ++i) {
            int value = rnd.next(1, 100);
            if (rnd.next(2) == 0) {
                points.push_back({rnd.next(2) == 0 ? -value : value, 0});
            } else {
                points.push_back({0, rnd.next(2) == 0 ? -value : value});
            }
        }
    } else if (mode == 1) {
        vector<pair<int, int>> corners = {
            {100, 100}, {100, -100}, {-100, 100}, {-100, -100},
        };
        shuffle(corners.begin(), corners.end());
        for (auto point : corners) points.push_back(point);
        while ((int)points.size() < t) {
            int x = rnd.any(vector<int>{-100, 100, rnd.next(-100, 100)});
            int y = rnd.any(vector<int>{-100, 100, rnd.next(-100, 100)});
            if (x == 0 && y == 0) x = 100;
            points.push_back({x, y});
        }
    } else if (mode == 2) {
        for (int i = 0; i < t; ++i) points.push_back(randomPoint(rnd.next(1, 12)));
    } else if (mode == 3) {
        for (int i = 0; i < t; ++i) {
            int magnitude = rnd.next(1, 100);
            int x = rnd.next(2) == 0 ? -magnitude : magnitude;
            int y = rnd.next(2) == 0 ? -magnitude : magnitude;
            points.push_back({x, y});
        }
    } else {
        for (int i = 0; i < t; ++i) points.push_back(randomPoint(100));
    }

    println((int)points.size());
    for (auto [x, y] : points) println(x, y);

    return 0;
}
