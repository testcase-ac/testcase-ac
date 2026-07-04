#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

struct Ship {
    int x;
    int y;
    int rocketSpeed;
    int virusSpeed;
};

Ship makeAxisShip(int dir, int distance, int rocketSpeed, int virusSpeed) {
    static const int dx[] = {1, 0, -1, 0};
    static const int dy[] = {0, 1, 0, -1};
    return {dx[dir] * distance, dy[dir] * distance, rocketSpeed, virusSpeed};
}

Ship makeRandomShip(int r, int rocketSpeed, int virusSpeed) {
    long long rr = 1LL * r * r;
    for (int tries = 0; tries < 10000; ++tries) {
        int limit = min(1000000, max(r + 20, 3 * r + 50));
        int x = rnd.next(-limit, limit);
        int y = rnd.next(-limit, limit);
        if (1LL * x * x + 1LL * y * y >= rr) {
            return {x, y, rocketSpeed, virusSpeed};
        }
    }

    return {r, 0, rocketSpeed, virusSpeed};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int r = rnd.next(1, 250);
        int k = rnd.next(1, 12);
        vector<Ship> ships;

        if (mode == 0) {
            k = 1;
            int distance = rnd.next(r, min(1000000, r + 500));
            ships.push_back(makeAxisShip(rnd.next(0, 3), distance, rnd.next(1, 1000), rnd.next(1, 1000)));
        } else if (mode == 1) {
            k = rnd.next(2, 8);
            int distance = rnd.next(r, min(1000000, r + 200));
            for (int i = 0; i < k; ++i) {
                ships.push_back(makeAxisShip(i % 4, distance, rnd.next(1, 500), rnd.next(1, 500)));
            }
        } else if (mode == 2) {
            k = rnd.next(2, 10);
            for (int i = 0; i < k; ++i) {
                int distance = rnd.next(r, min(1000000, r + 3));
                ships.push_back(makeAxisShip(rnd.next(0, 3), distance, rnd.next(1, 1000000), rnd.next(1, 1000000)));
            }
        } else if (mode == 3) {
            r = rnd.any(vector<int>{1, 2, 10, 1000, 1000000});
            k = rnd.next(1, 6);
            for (int i = 0; i < k; ++i) {
                int dir = rnd.next(0, 3);
                int distance = rnd.next(r, 1000000);
                ships.push_back(makeAxisShip(dir, distance, rnd.next(1, 1000000), rnd.next(1, 1000000)));
            }
        } else {
            k = rnd.next(3, 12);
            for (int i = 0; i < k; ++i) {
                ships.push_back(makeRandomShip(r, rnd.next(1, 2000), rnd.next(1, 2000)));
            }
        }

        shuffle(ships.begin(), ships.end());
        println(r, static_cast<int>(ships.size()));
        for (const Ship& ship : ships) {
            println(ship.x, ship.y, ship.rocketSpeed, ship.virusSpeed);
        }
    }

    return 0;
}
