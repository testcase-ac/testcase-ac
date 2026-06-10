#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Mineral {
    int x;
    int y;
    int v;
};

static void addMineral(vector<Mineral>& minerals, set<pair<int, int>>& used, int x, int y, int v) {
    if (x == 0 && y == 0) return;
    if (!used.insert({x, y}).second) return;
    minerals.push_back({x, y, v});
}

static int valueForMode(int mode, int i) {
    if (mode == 0) return rnd.next(1, 30);
    if (mode == 1) return (i % 3 == 0 ? rnd.next(1000, 100000000) : rnd.next(1, 20));
    if (mode == 2) return rnd.next(1, 5) * rnd.next(1, 5);
    return rnd.next(1, 100000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    vector<Mineral> minerals;
    set<pair<int, int>> used;

    if (mode == 0) {
        int maxX = rnd.next(1, 12);
        int maxY = rnd.next(1, 12);
        for (int x = 0; x <= maxX && (int)minerals.size() < n; ++x) {
            for (int y = 0; y <= maxY && (int)minerals.size() < n; ++y) {
                if (rnd.next(0, 2) == 0) addMineral(minerals, used, x, y, valueForMode(mode, minerals.size()));
            }
        }
    } else if (mode == 1) {
        int rows = rnd.next(2, 8);
        int cols = rnd.next(2, 8);
        for (int i = 0; (int)minerals.size() < n && i < rows * cols * 2; ++i) {
            int x = rnd.next(0, cols - 1) * rnd.next(1, 3);
            int y = rnd.next(0, rows - 1) * rnd.next(1, 3);
            addMineral(minerals, used, x, y, valueForMode(mode, minerals.size()));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int x = i + rnd.next(0, 1);
            int y = n - i + rnd.next(0, 1);
            addMineral(minerals, used, x, y, valueForMode(mode, i));
        }
    } else if (mode == 3) {
        int fixedX = rnd.next(0, 5);
        int fixedY = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            int x = (rnd.next(0, 1) == 0 ? fixedX : rnd.next(0, 12));
            int y = (rnd.next(0, 1) == 0 ? fixedY : rnd.next(0, 12));
            addMineral(minerals, used, x, y, valueForMode(mode, i));
        }
    } else {
        vector<pair<int, int>> candidates = {
            {0, 1}, {1, 0}, {100000, 0}, {0, 100000}, {100000, 100000},
            {99999, 1}, {1, 99999}, {50000, 50000}, {100000, 1}, {1, 100000}
        };
        shuffle(candidates.begin(), candidates.end());
        for (auto [x, y] : candidates) {
            if ((int)minerals.size() == n) break;
            addMineral(minerals, used, x, y, valueForMode(mode, minerals.size()));
        }
    }

    while ((int)minerals.size() < n) {
        int bound = rnd.next(3, 30);
        addMineral(minerals, used, rnd.next(0, bound), rnd.next(0, bound), valueForMode(mode, minerals.size()));
    }

    shuffle(minerals.begin(), minerals.end());

    int c;
    if (rnd.next(0, 4) == 0) {
        c = 1;
    } else if (rnd.next(0, 3) == 0) {
        c = n;
    } else {
        c = rnd.next(1, n);
    }

    println(n, c);
    for (const Mineral& m : minerals) {
        println(m.x, m.y, m.v);
    }

    return 0;
}
