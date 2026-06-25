#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int s = 1;
    vector<pair<int, int>> fish;
    set<pair<int, int>> used;

    auto addFish = [&](int x, int y) {
        if (1 <= x && x <= 100 && 1 <= y && y <= 100 &&
            used.insert({x, y}).second) {
            fish.push_back({x, y});
        }
    };

    auto addRandomFish = [&]() {
        while ((int)fish.size() < 100) {
            int x = rnd.next(1, 100);
            int y = rnd.next(1, 100);
            if (used.insert({x, y}).second) {
                fish.push_back({x, y});
                return;
            }
        }
    };

    if (mode == 0) {
        s = rnd.next(1, 6);
        int x0 = rnd.next(1, 100 - s);
        int y0 = rnd.next(1, 100 - s);
        for (int dx = 0; dx <= s; ++dx) {
            addFish(x0 + dx, y0);
            addFish(x0 + dx, y0 + s);
        }
        for (int dy = 1; dy < s; ++dy) {
            addFish(x0, y0 + dy);
            addFish(x0 + s, y0 + dy);
        }
        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            addRandomFish();
        }
    } else if (mode == 1) {
        s = rnd.next(2, 12);
        int x0 = rnd.next(1, 100 - s);
        int y0 = rnd.next(1, 100 - s);
        int inside = rnd.next(6, 18);
        for (int i = 0; i < inside; ++i) {
            addFish(rnd.next(x0, x0 + s), rnd.next(y0, y0 + s));
        }
        int outside = rnd.next(4, 12);
        for (int i = 0; i < outside; ++i) {
            if (rnd.next(0, 1) == 0) {
                addFish(rnd.next(x0, x0 + s), y0 + s + 1);
            } else {
                addFish(x0 + s + 1, rnd.next(y0, y0 + s));
            }
        }
    } else if (mode == 2) {
        s = rnd.next(10, 40);
        int clusters = rnd.next(2, 4);
        for (int c = 0; c < clusters; ++c) {
            int x0 = rnd.next(1, 100 - s);
            int y0 = rnd.next(1, 100 - s);
            int count = rnd.next(4, 12);
            for (int i = 0; i < count; ++i) {
                addFish(rnd.next(x0, x0 + s), rnd.next(y0, y0 + s));
            }
        }
    } else if (mode == 3) {
        s = rnd.next(90, 100);
        int n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            addRandomFish();
        }
        addFish(1, 1);
        addFish(100, 100);
    } else if (mode == 4) {
        s = 1;
        int n = rnd.next(8, 30);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(1, 50) * 2 - 1;
            int y = rnd.next(1, 50) * 2 - 1;
            addFish(x, y);
        }
    } else {
        s = rnd.next(1, 100);
        int n = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            addRandomFish();
        }
    }

    while (fish.empty()) {
        addRandomFish();
    }

    shuffle(fish.begin(), fish.end());

    println(s, (int)fish.size());
    for (auto [x, y] : fish) {
        println(x, y);
    }

    return 0;
}
