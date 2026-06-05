#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

struct Gear {
    int x;
    int y;
    int r;
};

int clampCoord(int v) {
    return max(-1000, min(1000, v));
}

Gear randomGear(int coordLimit, int maxRadius) {
    return {rnd.next(-coordLimit, coordLimit), rnd.next(-coordLimit, coordLimit), rnd.next(1, maxRadius)};
}

void printGears(const vector<Gear>& gears) {
    println((int)gears.size());
    for (const Gear& g : gears) println(g.x, g.y, g.r);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<Gear> gears;

    if (mode == 0) {
        gears.push_back(randomGear(1000, 1000));
    } else if (mode == 1) {
        int n = rnd.next(2, 12);
        int x = rnd.next(-20, 20);
        int y = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) gears.push_back({x, y, rnd.next(1, 30)});
    } else if (mode == 2) {
        int n = rnd.next(2, 10);
        int x = rnd.next(-30, 30);
        int y = rnd.next(-30, 30);
        int prevR = rnd.next(1, 12);
        gears.push_back({x, y, prevR});
        for (int i = 1; i < n; ++i) {
            int r = rnd.next(1, 12);
            x += prevR + r;
            gears.push_back({x, y + rnd.next(-1, 1), r});
            prevR = r;
        }
    } else if (mode == 3) {
        int clusters = rnd.next(2, 4);
        for (int c = 0; c < clusters; ++c) {
            int cx = rnd.next(-60, 60) + c * rnd.next(20, 80);
            int cy = rnd.next(-80, 80);
            int m = rnd.next(2, 5);
            for (int i = 0; i < m; ++i) {
                gears.push_back({clampCoord(cx + rnd.next(-8, 8)),
                                 clampCoord(cy + rnd.next(-8, 8)),
                                 rnd.next(3, 18)});
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 10);
        vector<int> coords = {-1000, -999, -500, 0, 500, 999, 1000};
        for (int i = 0; i < n; ++i) {
            int x = rnd.any(coords);
            int y = rnd.any(coords);
            int r = rnd.next(1, 1000);
            gears.push_back({x, y, r});
        }
    } else {
        int n = rnd.next(2, 18);
        int coordLimit = rnd.next(5, 120);
        int maxRadius = rnd.next(2, 40);
        for (int i = 0; i < n; ++i) gears.push_back(randomGear(coordLimit, maxRadius));
    }

    shuffle(gears.begin(), gears.end());
    printGears(gears);
    return 0;
}
