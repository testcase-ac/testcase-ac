#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int kMinCoord = 1;
const int kMaxCoord = 1000;

bool inside(int x, int y) {
    return kMinCoord <= x && x <= kMaxCoord && kMinCoord <= y && y <= kMaxCoord;
}

void addBale(set<pair<int, int>>& used, int tractorX, int tractorY, int x, int y) {
    if (!inside(x, y)) return;
    if (x == tractorX && y == tractorY) return;
    used.insert({x, y});
}

void addRandomBales(set<pair<int, int>>& used, int tractorX, int tractorY, int target) {
    while ((int)used.size() < target) {
        addBale(used, tractorX, tractorY, rnd.next(kMinCoord, kMaxCoord), rnd.next(kMinCoord, kMaxCoord));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int tractorX;
    int tractorY;
    set<pair<int, int>> used;

    if (mode == 0) {
        tractorX = rnd.next(kMinCoord, kMaxCoord);
        tractorY = rnd.next(kMinCoord, kMaxCoord);
        addRandomBales(used, tractorX, tractorY, rnd.next(1, 25));
    } else if (mode == 1) {
        tractorX = rnd.next(3, 998);
        tractorY = rnd.next(3, 998);
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (abs(dx) + abs(dy) == 1) {
                    addBale(used, tractorX, tractorY, tractorX + dx, tractorY + dy);
                }
            }
        }
        if (rnd.next(0, 1)) {
            addBale(used, tractorX, tractorY, tractorX - 1, tractorY - 1);
            addBale(used, tractorX, tractorY, tractorX + 1, tractorY + 1);
        }
        addRandomBales(used, tractorX, tractorY, rnd.next((int)used.size(), (int)used.size() + 18));
    } else if (mode == 2) {
        tractorX = rnd.next(10, 990);
        tractorY = rnd.next(10, 990);
        int x = rnd.next(max(kMinCoord, tractorX - 7), min(kMaxCoord, tractorX + 7));
        int y1 = rnd.next(max(kMinCoord, tractorY - 10), tractorY);
        int y2 = rnd.next(tractorY, min(kMaxCoord, tractorY + 10));
        for (int y = y1; y <= y2; ++y) {
            if (rnd.next(0, 5) != 0) addBale(used, tractorX, tractorY, x, y);
        }
        addRandomBales(used, tractorX, tractorY, rnd.next(max(1, (int)used.size()), (int)used.size() + 20));
    } else if (mode == 3) {
        tractorX = rnd.next(1, 12);
        tractorY = rnd.next(1, 12);
        int width = rnd.next(3, 9);
        int height = rnd.next(3, 9);
        for (int x = 1; x <= width; ++x) {
            for (int y = 1; y <= height; ++y) {
                if (rnd.next(0, 3) == 0) addBale(used, tractorX, tractorY, x, y);
            }
        }
        addRandomBales(used, tractorX, tractorY, rnd.next(max(1, (int)used.size()), max(1, (int)used.size()) + 10));
    } else if (mode == 4) {
        tractorX = rnd.next(990, 1000);
        tractorY = rnd.next(990, 1000);
        int count = rnd.next(8, 35);
        for (int i = 0; i < count; ++i) {
            int x = rnd.next(985, 1000);
            int y = rnd.next(985, 1000);
            addBale(used, tractorX, tractorY, x, y);
        }
        addRandomBales(used, tractorX, tractorY, max(1, (int)used.size()));
    } else {
        tractorX = rnd.next(2, 999);
        tractorY = rnd.next(2, 999);
        int radius = rnd.next(2, 5);
        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dy = -radius; dy <= radius; ++dy) {
                if (abs(dx) + abs(dy) == radius && rnd.next(0, 4) != 0) {
                    addBale(used, tractorX, tractorY, tractorX + dx, tractorY + dy);
                }
            }
        }
        addRandomBales(used, tractorX, tractorY, rnd.next(max(1, (int)used.size()), (int)used.size() + 16));
    }

    vector<pair<int, int>> bales(used.begin(), used.end());
    shuffle(bales.begin(), bales.end());

    println((int)bales.size(), tractorX, tractorY);
    for (auto bale : bales) {
        println(bale.first, bale.second);
    }

    return 0;
}
