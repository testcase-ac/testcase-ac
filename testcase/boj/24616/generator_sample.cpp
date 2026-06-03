#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int X_MAX = 1000000;
    vector<pair<int, int>> cows;
    set<pair<int, int>> used;

    auto addCow = [&](int x, int y) {
        x = max(0, min(X_MAX, x));
        y = max(0, min(10, y));
        if (used.insert({x, y}).second) cows.push_back({x, y});
    };

    int mode = rnd.next(0, 5);

    if (mode == 0) {
        addCow(rnd.next(0, X_MAX), rnd.next(0, 10));
    } else if (mode == 1) {
        int n = rnd.next(2, 8);
        int baseX = rnd.next(0, X_MAX);
        for (int i = 0; i < n; ++i) {
            addCow(baseX, i % 11);
        }
    } else if (mode == 2) {
        int n = rnd.next(8, 35);
        int baseX = rnd.next(0, X_MAX - 50);
        while ((int)cows.size() < n) {
            addCow(baseX + rnd.next(0, 50), rnd.next(0, 10));
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 35);
        while ((int)cows.size() < n) {
            int side = rnd.next(0, 1);
            int x = side == 0 ? rnd.next(0, 200) : X_MAX - rnd.next(0, 200);
            addCow(x, rnd.next(0, 10));
        }
    } else if (mode == 4) {
        int columns = rnd.next(2, 12);
        int step = rnd.next(1, 20000);
        int maxStart = max(0, X_MAX - step * (columns - 1));
        int start = rnd.next(0, maxStart);
        for (int c = 0; c < columns; ++c) {
            int x = start + c * step;
            int countAtX = rnd.next(1, 11);
            vector<int> ys;
            for (int y = 0; y <= 10; ++y) ys.push_back(y);
            shuffle(ys.begin(), ys.end());
            for (int i = 0; i < countAtX; ++i) addCow(x, ys[i]);
        }
    } else {
        int n = rnd.next(15, 60);
        int xLimit = rnd.next(200, X_MAX);
        while ((int)cows.size() < n) {
            addCow(rnd.next(0, xLimit), rnd.next(0, 10));
        }
    }

    shuffle(cows.begin(), cows.end());

    println((int)cows.size());
    for (auto [x, y] : cows) {
        println(x, y);
    }

    return 0;
}
