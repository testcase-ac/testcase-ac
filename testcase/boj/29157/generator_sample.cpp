#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m, targetK;

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
        targetK = rnd.next(0, min(5, (n + 1) * (m + 1) - 2));
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        m = rnd.next(2, 20);
        targetK = rnd.next(1, min(12, (n + 1) * (m + 1) - 2));
    } else if (mode == 2) {
        n = rnd.next(5, 50);
        m = rnd.next(5, 50);
        targetK = rnd.next(3, 16);
    } else if (mode == 3) {
        n = rnd.next(10, 200);
        m = rnd.next(10, 200);
        targetK = rnd.next(8, 20);
    } else if (mode == 4) {
        n = rnd.next(1, 1000000);
        m = rnd.next(1, 1000000);
        targetK = rnd.next(0, 20);
    } else {
        n = 1000000;
        m = 1000000;
        targetK = rnd.next(12, 20);
    }

    set<pair<int, int>> used;
    vector<pair<int, int>> bombs;

    auto addBomb = [&](int x, int y) {
        if (x < 0 || x > n || y < 0 || y > m) return;
        if ((x == 0 && y == 0) || (x == n && y == m)) return;
        if (used.insert({x, y}).second) bombs.push_back({x, y});
    };

    if (mode == 1) {
        addBomb(0, rnd.next(1, m));
        addBomb(rnd.next(1, n), 0);
        addBomb(n, rnd.next(0, m - 1));
        addBomb(rnd.next(0, n - 1), m);
    } else if (mode == 2) {
        int x = 0;
        int y = 0;
        while ((int)bombs.size() < targetK && (x < n || y < m)) {
            if (x < n) x += rnd.next(0, min(3, n - x));
            if (y < m) y += rnd.next(0, min(3, m - y));
            if (x == 0 && y == 0) {
                if (x < n) ++x;
                else ++y;
            }
            addBomb(x, y);
            if (x == n && y == m) break;
            if (x == n && y == m - 1) --x;
            if (x == n - 1 && y == m) --y;
        }
    } else if (mode == 3) {
        for (int i = 0; i < targetK; ++i) {
            int x = rnd.next(0, n);
            int y = m - rnd.next(0, m);
            addBomb(x, y);
        }
    } else if (mode == 5) {
        vector<pair<int, int>> anchors = {
            {0, 1},
            {1, 0},
            {n, m - 1},
            {n - 1, m},
            {1, 1},
            {n / 2, m / 2},
            {n / 3, 2 * m / 3},
            {2 * n / 3, m / 3},
        };
        shuffle(anchors.begin(), anchors.end());
        for (auto [x, y] : anchors) addBomb(x, y);
    }

    int attempts = 0;
    while ((int)bombs.size() < targetK && attempts < 500) {
        ++attempts;
        int x, y;
        if (mode == 1 && rnd.next(0, 1)) {
            if (rnd.next(0, 1)) {
                x = rnd.next(0, n);
                y = rnd.any(vector<int>{0, m});
            } else {
                x = rnd.any(vector<int>{0, n});
                y = rnd.next(0, m);
            }
        } else {
            x = rnd.next(0, n);
            y = rnd.next(0, m);
        }
        addBomb(x, y);
    }

    for (int x = 0; (int)bombs.size() < targetK && x <= n; ++x) {
        for (int y = 0; (int)bombs.size() < targetK && y <= m; ++y) {
            addBomb(x, y);
        }
    }

    shuffle(bombs.begin(), bombs.end());

    println(n, m, (int)bombs.size());
    for (auto [x, y] : bombs) {
        println(x, y);
    }

    return 0;
}
