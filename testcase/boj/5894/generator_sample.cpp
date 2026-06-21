#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int distinctCoord(int lo, int hi, int forbidden) {
    int x = rnd.next(lo, hi - 1);
    if (x >= forbidden) ++x;
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cows;
    int mode = rnd.next(5);

    if (mode == 0) {
        int n = rnd.next(1, 10);
        int lo = rnd.next(-6, 0);
        int hi = rnd.next(0, 6);
        for (int i = 0; i < n; ++i) {
            cows.push_back({rnd.next(lo, hi), rnd.next(lo, hi)});
        }
    } else if (mode == 1) {
        int n = rnd.next(1, 10);
        bool vertical = rnd.next(2);
        int fixed = rnd.next(-4, 4);
        for (int i = 0; i < n; ++i) {
            int moving = rnd.next(-8, 8);
            cows.push_back(vertical ? make_pair(fixed, moving) : make_pair(moving, fixed));
        }
    } else if (mode == 2) {
        int x1 = distinctCoord(-5, 5, 0);
        int x2 = distinctCoord(-5, 5, x1);
        int y1 = distinctCoord(-5, 5, 0);
        int y2 = distinctCoord(-5, 5, y1);
        vector<pair<int, int>> corners = {{x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}};
        shuffle(corners.begin(), corners.end());
        int keep = rnd.next(3, 4);
        cows.insert(cows.end(), corners.begin(), corners.begin() + keep);
        int extras = rnd.next(0, 10 - keep);
        for (int i = 0; i < extras; ++i) {
            cows.push_back({rnd.any(vector<int>{x1, x2}), rnd.any(vector<int>{y1, y2})});
        }
    } else if (mode == 3) {
        int n = rnd.next(1, 10);
        vector<pair<int, int>> pool = {
            {0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-2, 0}, {2, 0}, {0, -2}, {0, 2}
        };
        for (int i = 0; i < n; ++i) {
            cows.push_back(rnd.any(pool));
        }
    } else {
        int n = rnd.next(4, 10);
        int x = 0;
        int y = 0;
        for (int i = 0; i < n; ++i) {
            if (rnd.next(2)) {
                x += rnd.any(vector<int>{-3, -2, -1, 1, 2, 3});
            } else {
                y += rnd.any(vector<int>{-3, -2, -1, 1, 2, 3});
            }
            x = max(-10, min(10, x));
            y = max(-10, min(10, y));
            cows.push_back({x, y});
        }
        shuffle(cows.begin(), cows.end());
    }

    println(static_cast<int>(cows.size()));
    for (auto [x, y] : cows) {
        println(x, y);
    }

    return 0;
}
