#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Flower {
    int x;
    int y;
    int c;
};

void addFlower(vector<Flower>& flowers, set<pair<int, int>>& used, int x, int y, int c) {
    if (used.insert({x, y}).second) {
        flowers.push_back({x, y, c});
    }
}

int randEnergy(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(900000000, 1000000000);
    return rnd.next(1, 1000000000);
}

vector<Flower> makeCase(int n, int mode) {
    vector<Flower> flowers;
    set<pair<int, int>> used;

    if (mode == 0) {
        while ((int)flowers.size() < n) {
            addFlower(flowers, used, rnd.next(0, 8), rnd.next(0, 8), randEnergy(mode));
        }
    } else if (mode == 1) {
        int y = rnd.next(0, 12);
        while ((int)flowers.size() < n) {
            addFlower(flowers, used, rnd.next(0, 20), y, randEnergy(mode));
        }
    } else if (mode == 2) {
        while ((int)flowers.size() < n) {
            int y = rnd.next(0, 5) * 2;
            int x = rnd.next(0, 18);
            addFlower(flowers, used, x, y, randEnergy(mode));
        }
    } else if (mode == 3) {
        vector<pair<int, int>> anchors = {
            {0, 0}, {0, 1000000000}, {100000, 0}, {100000, 1000000000},
            {1, 999999999}, {99999, 1}, {50000, 500000000}
        };
        shuffle(anchors.begin(), anchors.end());
        for (auto [x, y] : anchors) {
            if ((int)flowers.size() == n) break;
            addFlower(flowers, used, x, y, randEnergy(mode));
        }
        while ((int)flowers.size() < n) {
            int x = rnd.any(vector<int>{0, 1, 99999, 100000, rnd.next(0, 100000)});
            int y = rnd.any(vector<int>{0, 1, 999999999, 1000000000, rnd.next(0, 1000000000)});
            addFlower(flowers, used, x, y, randEnergy(mode));
        }
    } else {
        int layers = rnd.next(3, 7);
        while ((int)flowers.size() < n) {
            int layer = rnd.next(0, layers - 1);
            int y = 1000000000 - layer * rnd.next(1, 1000);
            int x = rnd.next(0, 100000);
            addFlower(flowers, used, x, y, randEnergy(mode));
        }
    }

    shuffle(flowers.begin(), flowers.end());
    return flowers;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 7);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc == 0 ? 0 : rnd.next(0, 4);
        int n;
        if (mode == 4) {
            n = rnd.next(25, 60);
        } else if (mode == 3) {
            n = rnd.next(4, 12);
        } else {
            n = rnd.next(1, 18);
        }

        int e;
        if (mode == 0) {
            e = rnd.next(0, 20);
        } else if (mode == 1) {
            e = rnd.next(900000000, 1000000000);
        } else if (mode == 2) {
            e = rnd.any(vector<int>{0, 1, 2, 10, 1000000000});
        } else {
            e = rnd.next(0, 1000000000);
        }

        vector<Flower> flowers = makeCase(n, mode);
        println((int)flowers.size(), e);
        for (const Flower& f : flowers) {
            println(f.x, f.y, f.c);
        }
    }

    return 0;
}
