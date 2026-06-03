#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MIN_COORD = -100000000;
const int MAX_COORD = 100000000;

void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int x, int y) {
    if (used.insert({x, y}).second) points.push_back({x, y});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        addPoint(points, used, rnd.next(-10, 10), rnd.next(-10, 10));
    } else if (mode == 1) {
        int columns = rnd.next(2, 8);
        int baseX = rnd.next(-30, 10);
        int step = rnd.next(1, 10);
        for (int c = 0; c < columns; ++c) {
            int x = baseX + c * step;
            int cnt = rnd.next(1, 4);
            int baseY = rnd.next(-40, 40);
            for (int j = 0; j < cnt; ++j) {
                int y = baseY + rnd.next(-8, 8) + j * rnd.next(1, 5);
                addPoint(points, used, x, y);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(4, 24);
        int limit = rnd.next(3, 50);
        while (static_cast<int>(points.size()) < n) {
            addPoint(points, used, rnd.next(-limit, limit), rnd.next(-limit, limit));
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 18);
        int x = rnd.next(-100, -20);
        int y = rnd.next(-80, 80);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(1, 20);
            y += (i % 2 == 0 ? 1 : -1) * rnd.next(5, 35);
            addPoint(points, used, x, y);
            if (rnd.next(0, 2) == 0) addPoint(points, used, x, y + rnd.next(1, 20));
        }
    } else {
        vector<pair<int, int>> extreme = {
            {MIN_COORD, MIN_COORD},
            {MIN_COORD, MAX_COORD},
            {0, 0},
            {MAX_COORD, MIN_COORD},
            {MAX_COORD, MAX_COORD},
        };
        shuffle(extreme.begin(), extreme.end());
        int take = rnd.next(2, static_cast<int>(extreme.size()));
        for (int i = 0; i < take; ++i) addPoint(points, used, extreme[i].first, extreme[i].second);

        int extra = rnd.next(0, 8);
        while (extra--) {
            addPoint(points, used, rnd.next(-1000, 1000), rnd.next(-1000, 1000));
        }
    }

    shuffle(points.begin(), points.end());
    println(static_cast<int>(points.size()));
    for (auto [x, y] : points) println(x, y);

    return 0;
}
