#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int COORD_MAX = 10000;

int clampCoord(int x) {
    return max(0, min(COORD_MAX, x));
}

pair<int, int> randomPoint() {
    return {rnd.next(0, COORD_MAX), rnd.next(0, COORD_MAX)};
}

pair<int, int> nearbyPoint(int x, int y, int span) {
    return {clampCoord(x + rnd.next(-span, span)), clampCoord(y + rnd.next(-span, span))};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int g = rnd.next(1, 35);
    int m = rnd.next(1, 18);
    vector<pair<int, int>> goblins;
    vector<pair<pair<int, int>, int>> sprinklers;

    if (mode == 0) {
        pair<int, int> base = randomPoint();
        int radius = rnd.next(1, 100);
        g = rnd.next(1, 30);
        m = rnd.next(1, 12);

        for (int i = 0; i < g; ++i) {
            if (rnd.next(0, 99) < 35) {
                goblins.push_back(base);
            } else {
                goblins.push_back(nearbyPoint(base.first, base.second, radius + rnd.next(0, 6)));
            }
        }
        for (int i = 0; i < m; ++i) {
            auto center = nearbyPoint(base.first, base.second, 8);
            sprinklers.push_back({center, rnd.next(1, 100)});
        }
    } else if (mode == 1) {
        vector<pair<int, int>> corners = {{0, 0}, {0, COORD_MAX}, {COORD_MAX, 0}, {COORD_MAX, COORD_MAX}};
        shuffle(corners.begin(), corners.end());
        g = rnd.next(4, 28);
        m = rnd.next(2, 10);

        for (int i = 0; i < g; ++i) {
            auto corner = rnd.any(corners);
            goblins.push_back(nearbyPoint(corner.first, corner.second, 120));
        }
        for (int i = 0; i < m; ++i) {
            auto corner = rnd.any(corners);
            sprinklers.push_back({nearbyPoint(corner.first, corner.second, 40), rnd.next(1, 100)});
        }
    } else if (mode == 2) {
        pair<int, int> center = randomPoint();
        int radius = rnd.next(1, 100);
        vector<pair<int, int>> offsets = {{radius, 0}, {-radius, 0}, {0, radius}, {0, -radius}};
        g = rnd.next(4, 24);
        m = rnd.next(1, 8);

        for (int i = 0; i < g; ++i) {
            auto off = rnd.any(offsets);
            if (rnd.next(0, 99) < 50) {
                off.first += rnd.next(-1, 1);
                off.second += rnd.next(-1, 1);
            }
            goblins.push_back({clampCoord(center.first + off.first), clampCoord(center.second + off.second)});
        }
        sprinklers.push_back({center, radius});
        for (int i = 1; i < m; ++i) {
            sprinklers.push_back({nearbyPoint(center.first, center.second, radius), rnd.next(1, 100)});
        }
    } else if (mode == 3) {
        g = rnd.next(10, 35);
        m = rnd.next(1, 5);
        int y = rnd.next(0, COORD_MAX);
        int step = rnd.next(1, 100);
        int start = rnd.next(0, COORD_MAX);

        for (int i = 0; i < g; ++i) {
            goblins.push_back({clampCoord(start + (i - g / 2) * step), clampCoord(y + rnd.next(-2, 2))});
        }
        for (int i = 0; i < m; ++i) {
            int x = clampCoord(start + rnd.next(-g / 2, g / 2) * step);
            sprinklers.push_back({{x, y}, rnd.next(1, 100)});
        }
    } else {
        pair<int, int> duplicate = randomPoint();
        g = rnd.next(1, 32);
        m = rnd.next(1, 16);

        for (int i = 0; i < g; ++i) {
            if (rnd.next(0, 99) < 45) {
                goblins.push_back(duplicate);
            } else {
                goblins.push_back(randomPoint());
            }
        }
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 99) < 35) {
                sprinklers.push_back({duplicate, rnd.next(1, 100)});
            } else {
                sprinklers.push_back({randomPoint(), rnd.next(1, 100)});
            }
        }
    }

    println((int)goblins.size());
    for (auto p : goblins) {
        println(p.first, p.second);
    }
    println((int)sprinklers.size());
    for (auto s : sprinklers) {
        println(s.first.first, s.first.second, s.second);
    }

    return 0;
}
