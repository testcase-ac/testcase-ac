#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addPoint(vector<pair<int, int>>& guards, set<pair<int, int>>& used,
                     int x, int y) {
    if (used.emplace(x, y).second) {
        guards.emplace_back(x, y);
    }
}

static int clampCoord(int value, int L) {
    return max(0, min(L - 1, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int L;
    if (mode == 5) {
        L = rnd.next(1000000, 100000000);
    } else {
        L = rnd.next(1, 40);
    }

    vector<pair<int, int>> guards;
    set<pair<int, int>> used;

    if (mode == 0) {
        int target = rnd.next(1, min(L * L, 12));
        while ((int)guards.size() < target) {
            addPoint(guards, used, rnd.next(0, L - 1), rnd.next(0, L - 1));
        }
    } else if (mode == 1) {
        int target = rnd.next(1, min(L * L, 16));
        while ((int)guards.size() < target) {
            int side = rnd.next(0, 3);
            int t = rnd.next(0, L - 1);
            if (side == 0) addPoint(guards, used, t, 0);
            if (side == 1) addPoint(guards, used, t, L - 1);
            if (side == 2) addPoint(guards, used, 0, t);
            if (side == 3) addPoint(guards, used, L - 1, t);
        }
    } else if (mode == 2) {
        int target = rnd.next(1, min(L, 18));
        int offset = rnd.next(-(L - 1), L - 1);
        for (int x = 0; x < L && (int)guards.size() < target; ++x) {
            int y = x - offset;
            if (0 <= y && y < L) addPoint(guards, used, x, y);
        }
        while ((int)guards.size() < target) {
            int x = rnd.next(0, L - 1);
            addPoint(guards, used, x, clampCoord(x - offset, L));
        }
    } else if (mode == 3) {
        int target = rnd.next(1, min(L, 18));
        int sum = rnd.next(0, 2 * (L - 1));
        for (int x = 0; x < L && (int)guards.size() < target; ++x) {
            int y = sum - x;
            if (0 <= y && y < L) addPoint(guards, used, x, y);
        }
        while ((int)guards.size() < target) {
            int x = rnd.next(0, L - 1);
            addPoint(guards, used, x, clampCoord(sum - x, L));
        }
    } else if (mode == 4) {
        int centerX = rnd.next(0, L - 1);
        int centerY = rnd.next(0, L - 1);
        int radius = rnd.next(0, max(0, L - 1));
        for (int dx = -radius; dx <= radius; ++dx) {
            if (rnd.next(0, 1)) {
                addPoint(guards, used, clampCoord(centerX + dx, L),
                         clampCoord(centerY + abs(dx), L));
            }
            if (rnd.next(0, 1)) {
                addPoint(guards, used, clampCoord(centerX + dx, L),
                         clampCoord(centerY - abs(dx), L));
            }
        }
        while (guards.empty()) {
            addPoint(guards, used, centerX, centerY);
        }
    } else {
        int target = rnd.next(4, 24);
        vector<int> coords = {0, 1, L / 2, L - 2, L - 1};
        for (int i = 0; i < target; ++i) {
            int x = rnd.any(coords);
            int y = rnd.any(coords);
            if (rnd.next(0, 2) == 0) x = rnd.next(0, L - 1);
            if (rnd.next(0, 2) == 0) y = rnd.next(0, L - 1);
            addPoint(guards, used, clampCoord(x, L), clampCoord(y, L));
        }
        while (guards.empty()) {
            addPoint(guards, used, 0, 0);
        }
    }

    shuffle(guards.begin(), guards.end());
    println(L, (int)guards.size());
    for (auto [x, y] : guards) {
        println(x, y);
    }

    return 0;
}
