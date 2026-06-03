#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MAX_COORD = 1000;

void addPoint(vector<pair<int, int>>& cows, set<pair<int, int>>& used, int x, int y) {
    if (0 <= x && x <= MAX_COORD && 0 <= y && y <= MAX_COORD && used.insert({x, y}).second) {
        cows.push_back({x, y});
    }
}

void addRandomUnique(vector<pair<int, int>>& cows, set<pair<int, int>>& used, int target) {
    while ((int)cows.size() < target) {
        addPoint(cows, used, rnd.next(0, MAX_COORD), rnd.next(0, MAX_COORD));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cows;
    set<pair<int, int>> used;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 25);
        addRandomUnique(cows, used, n);
    } else if (mode == 1) {
        int len = rnd.next(2, 35);
        int horizontal = rnd.next(0, 1);
        int x = rnd.next(0, horizontal ? MAX_COORD - len + 1 : MAX_COORD);
        int y = rnd.next(0, horizontal ? MAX_COORD : MAX_COORD - len + 1);
        for (int i = 0; i < len; ++i) {
            addPoint(cows, used, x + (horizontal ? i : 0), y + (horizontal ? 0 : i));
        }
    } else if (mode == 2) {
        int width = rnd.next(2, 8);
        int height = rnd.next(2, 8);
        int x0 = rnd.next(0, MAX_COORD - width + 1);
        int y0 = rnd.next(0, MAX_COORD - height + 1);
        double skip = rnd.next(0.05, 0.35);
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (rnd.next() >= skip) {
                    addPoint(cows, used, x0 + x, y0 + y);
                }
            }
        }
    } else if (mode == 3) {
        int groups = rnd.next(1, 5);
        for (int g = 0; g < groups; ++g) {
            int x = rnd.next(1, MAX_COORD - 1);
            int y = rnd.next(1, MAX_COORD - 1);
            vector<pair<int, int>> cross = {{x, y}, {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
            shuffle(cross.begin(), cross.end());
            int take = rnd.next(3, 5);
            for (int i = 0; i < take; ++i) {
                addPoint(cows, used, cross[i].first, cross[i].second);
            }
        }
    } else {
        int x0 = rnd.next(2, MAX_COORD - 5);
        int y0 = rnd.next(2, MAX_COORD - 5);
        int steps = rnd.next(8, 35);
        int x = x0, y = y0;
        addPoint(cows, used, x, y);
        for (int i = 1; i < steps; ++i) {
            int dir = rnd.next(0, 3);
            if (dir == 0) ++x;
            if (dir == 1) --x;
            if (dir == 2) ++y;
            if (dir == 3) --y;
            x = min(MAX_COORD, max(0, x));
            y = min(MAX_COORD, max(0, y));
            addPoint(cows, used, x, y);
        }
        addRandomUnique(cows, used, max(1, steps / 2));
    }

    if (cows.empty()) {
        addPoint(cows, used, rnd.next(0, MAX_COORD), rnd.next(0, MAX_COORD));
    }

    shuffle(cows.begin(), cows.end());
    println((int)cows.size());
    for (auto [x, y] : cows) {
        println(x, y);
    }

    return 0;
}
