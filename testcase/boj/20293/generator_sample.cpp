#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Store {
    int r;
    int c;
    int f;
};

static void addStore(vector<Store>& stores, set<pair<int, int>>& used,
                     int r, int c, int f, int rows, int cols) {
    if (r < 1 || r > rows || c < 1 || c > cols) return;
    if ((r == 1 && c == 1) || (r == rows && c == cols)) return;
    if (!used.insert({r, c}).second) return;
    stores.push_back({r, c, f});
}

static void addRandomStore(vector<Store>& stores, set<pair<int, int>>& used,
                           int rows, int cols, int maxFuel) {
    for (int tries = 0; tries < 200 && (int)stores.size() < 1000; ++tries) {
        int r = rnd.next(1, rows);
        int c = rnd.next(1, cols);
        if ((r == 1 && c == 1) || (r == rows && c == cols)) continue;
        if (!used.insert({r, c}).second) continue;
        stores.push_back({r, c, rnd.next(0, maxFuel)});
        return;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int rows = rnd.next(2, 18);
    int cols = rnd.next(2, 18);
    vector<Store> stores;
    set<pair<int, int>> used;

    if (mode == 0) {
        rows = rnd.next(2, 3000);
        cols = rnd.next(2, 3000);
    } else if (mode == 1) {
        int len = rnd.next(1, 12);
        rows = rnd.next(len + 2, min(3000, len * 4 + 8));
        cols = rnd.next(len + 2, min(3000, len * 4 + 8));
        int r = 1, c = 1;
        for (int i = 0; i < len; ++i) {
            r += rnd.next(0, max(1, (rows - r) / max(1, len - i)));
            c += rnd.next(0, max(1, (cols - c) / max(1, len - i)));
            if (r == 1 && c == 1) c = min(cols - 1, c + 1);
            if (r == rows && c == cols) r = max(1, r - 1);
            addStore(stores, used, r, c, rnd.next(0, 100), rows, cols);
        }
    } else if (mode == 2) {
        rows = rnd.next(4, 30);
        cols = rnd.next(4, 30);
        int count = rnd.next(3, 18);
        for (int i = 0; i < count; ++i) {
            int edge = rnd.next(0, 3);
            int r = edge == 0 ? 1 : edge == 1 ? rows : rnd.next(1, rows);
            int c = edge == 2 ? 1 : edge == 3 ? cols : rnd.next(1, cols);
            addStore(stores, used, r, c, rnd.next(0, 100), rows, cols);
        }
    } else if (mode == 3) {
        rows = rnd.next(5, 25);
        cols = rnd.next(5, 25);
        int centerR = rnd.next(2, rows - 1);
        int centerC = rnd.next(2, cols - 1);
        int count = rnd.next(8, 35);
        for (int i = 0; i < count; ++i) {
            int r = min(rows, max(1, centerR + rnd.next(-3, 3)));
            int c = min(cols, max(1, centerC + rnd.next(-3, 3)));
            addStore(stores, used, r, c, rnd.next(0, 100), rows, cols);
        }
    } else if (mode == 4) {
        rows = rnd.next(2500, 3000);
        cols = rnd.next(2500, 3000);
        int count = rnd.next(1, 25);
        for (int i = 0; i < count; ++i) {
            int r = rnd.next(1, rows);
            int c = rnd.next(1, cols);
            int fuel = rnd.next(0, 100);
            addStore(stores, used, r, c, fuel, rows, cols);
        }
    } else {
        rows = rnd.next(8, 40);
        cols = rnd.next(8, 40);
        int count = rnd.next(20, 70);
        for (int i = 0; i < count; ++i) {
            addRandomStore(stores, used, rows, cols, rnd.next(20, 100));
        }
    }

    shuffle(stores.begin(), stores.end());

    println(rows, cols);
    println((int)stores.size());
    for (const Store& store : stores) {
        println(store.r, store.c, store.f);
    }

    return 0;
}
