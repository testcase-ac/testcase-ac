#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_COORD = 100000000;
const int MAX_SPEED = 1000000;

int clampCoord(int value) {
    return max(1, min(MAX_COORD, value));
}

int speedNear(int center) {
    int delta = rnd.next(-5, 5);
    return max(1, min(MAX_SPEED, center + delta));
}

vector<int> makeSkis(int vh) {
    int count = rnd.next(3, 14);
    vector<int> skis;

    skis.push_back(1);
    skis.push_back(speedNear(vh));
    skis.push_back(speedNear(max(1, vh / 2)));
    if (rnd.next(0, 2) == 0) skis.push_back(MAX_SPEED);

    while ((int)skis.size() < count) {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            skis.push_back(rnd.next(1, 20));
        } else if (mode == 1) {
            skis.push_back(speedNear(vh));
        } else if (mode == 2) {
            skis.push_back(rnd.next(1, min(MAX_SPEED, max(30, vh * 3))));
        } else if (mode == 3) {
            skis.push_back(MAX_SPEED - rnd.next(0, 30));
        } else {
            skis.push_back(rnd.next(1, MAX_SPEED));
        }
    }

    shuffle(skis.begin(), skis.end());
    return skis;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int w;
    int vh;
    vector<pair<int, int>> gates;

    if (mode == 0) {
        w = rnd.next(1, 20);
        vh = rnd.next(1, 20);
        gates.push_back({rnd.next(1, 60), rnd.next(1, 60)});
    } else if (mode == 1) {
        w = rnd.next(3, 30);
        vh = rnd.next(1, 40);
        int n = rnd.next(2, 10);
        int x = rnd.next(1, 80);
        int y = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            x = clampCoord(x + rnd.next(-w, w));
            gates.push_back({x, y});
            y += rnd.next(1, 10);
        }
    } else if (mode == 2) {
        w = rnd.next(1, 8);
        vh = rnd.next(1, 12);
        int n = rnd.next(3, 12);
        int low = rnd.next(1, 20);
        int high = rnd.next(40, 140);
        int y = 1;
        for (int i = 0; i < n; ++i) {
            int jitter = rnd.next(-3, 3);
            int x = (i % 2 == 0) ? low + jitter : high + jitter;
            gates.push_back({clampCoord(x), y});
            y += rnd.next(1, 4);
        }
    } else if (mode == 3) {
        w = rnd.any(vector<int>{1, 2, 1000000, 50000000, 100000000});
        vh = rnd.any(vector<int>{1, 2, 999999, 1000000});
        int n = rnd.next(2, 8);
        int y = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(0, 1) ? rnd.next(1, 40) : MAX_COORD - rnd.next(0, 40);
            gates.push_back({x, y});
            y += rnd.next(1000000, 10000000);
            if (y > MAX_COORD) y = MAX_COORD;
        }
    } else if (mode == 4) {
        w = rnd.next(1, 3);
        vh = rnd.next(1, 6);
        int n = rnd.next(4, 14);
        int y = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            int block = i % 3;
            int x = block == 0 ? rnd.next(1, 10) : block == 1 ? rnd.next(60, 90) : rnd.next(25, 35);
            gates.push_back({x, y});
            y += 1;
        }
    } else {
        w = rnd.next(1, 100);
        vh = rnd.next(1, 200);
        int n = rnd.next(15, 40);
        int x = rnd.next(1, 1000);
        int y = 1;
        int drift = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            x = clampCoord(x + drift + rnd.next(-30, 30));
            gates.push_back({x, y});
            y += rnd.next(1, 6);
        }
    }

    for (int i = 1; i < (int)gates.size(); ++i) {
        if (gates[i].second <= gates[i - 1].second) {
            gates[i].second = gates[i - 1].second + 1;
        }
    }

    vector<int> skis = makeSkis(vh);

    println(w, vh, (int)gates.size());
    for (auto [x, y] : gates) {
        println(x, y);
    }
    println((int)skis.size());
    for (int speed : skis) {
        println(speed);
    }

    return 0;
}
