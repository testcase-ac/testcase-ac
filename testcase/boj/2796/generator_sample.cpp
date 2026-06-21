#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Friend {
    int x;
    int y;
    int p;
};

int clampCoord(int value) {
    return min(200000, max(0, value));
}

Friend makeFriend(int x, int y, int p) {
    return {clampCoord(x), clampCoord(y), min(200000, max(0, p))};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 16);
    vector<Friend> friends;
    friends.reserve(n);

    if (mode == 0) {
        int baseX = rnd.next(0, 40);
        int baseY = rnd.next(0, 40);
        int pMax = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            friends.push_back(makeFriend(baseX + rnd.next(-10, 10),
                                         baseY + rnd.next(-10, 10),
                                         rnd.next(0, pMax)));
        }
    } else if (mode == 1) {
        int x = rnd.next(0, 30);
        int y = rnd.next(0, 30);
        int step = rnd.next(3, 18);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(0, min(6, step));
            friends.push_back(makeFriend(x + i * step + rnd.next(-1, 1),
                                         y + rnd.next(-3, 3),
                                         p));
        }
    } else if (mode == 2) {
        int x = rnd.next(20, 80);
        int y = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            x += rnd.next(-18, 18);
            y += rnd.next(-18, 18);
            friends.push_back(makeFriend(x, y, rnd.next(0, 12)));
        }
    } else if (mode == 3) {
        vector<pair<int, int>> corners = {{0, 0}, {0, 200000}, {200000, 0}, {200000, 200000}};
        shuffle(corners.begin(), corners.end());
        for (int i = 0; i < n; ++i) {
            auto corner = corners[i % corners.size()];
            int dx = rnd.next(0, 25);
            int dy = rnd.next(0, 25);
            int x = corner.first == 0 ? dx : 200000 - dx;
            int y = corner.second == 0 ? dy : 200000 - dy;
            friends.push_back(makeFriend(x, y, rnd.next(0, 30)));
        }
    } else if (mode == 4) {
        int x = rnd.next(0, 200000);
        int y = rnd.next(0, 200000);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(150000, 200000);
            friends.push_back(makeFriend(x + rnd.next(-1000, 1000),
                                         y + rnd.next(-1000, 1000),
                                         p));
        }
    } else {
        int x = rnd.next(0, 200000);
        int y = rnd.next(0, 200000);
        int p = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                p = rnd.next(0, 20);
            }
            friends.push_back(makeFriend(x, y, p));
            x = clampCoord(x + rnd.next(-50, 50));
            y = clampCoord(y + rnd.next(-50, 50));
        }
    }

    println(static_cast<int>(friends.size()));
    for (const Friend& f : friends) {
        println(f.x, f.y, f.p);
    }

    return 0;
}
