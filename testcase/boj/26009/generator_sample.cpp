#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int dist(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

int maxAllowedD(int n, int m, int r, int c) {
    return min(dist(r, c, 1, 1), dist(r, c, n, m)) - 1;
}

void addZone(vector<tuple<int, int, int>>& zones, int n, int m, int r, int c, int d) {
    int limit = maxAllowedD(n, m, r, c);
    if (limit < 0) return;
    zones.emplace_back(r, c, min(d, limit));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = 0, m = 0;
    vector<tuple<int, int, int>> zones;

    if (mode == 0) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
        int k = rnd.next(1, min(8, n * m - 2));
        vector<pair<int, int>> cells;
        for (int r = 1; r <= n; ++r) {
            for (int c = 1; c <= m; ++c) {
                if ((r == 1 && c == 1) || (r == n && c == m)) continue;
                cells.push_back({r, c});
            }
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < k; ++i) {
            addZone(zones, n, m, cells[i].first, cells[i].second, 0);
        }
    } else if (mode == 1) {
        n = rnd.next(6, 14);
        m = rnd.next(6, 14);
        int k = rnd.next(5, 24);
        for (int i = 0; i < k; ++i) {
            int r = rnd.next(1, n);
            int c = rnd.next(1, m);
            int limit = maxAllowedD(n, m, r, c);
            if (limit < 0) {
                --i;
                continue;
            }
            int bias = rnd.next(3);
            int d = bias == 0 ? 0 : rnd.next(0, min(limit, rnd.next(1, 5)));
            zones.emplace_back(r, c, d);
        }
    } else if (mode == 2) {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
        int blockCol = rnd.next(2, m - 1);
        for (int r = 2; r <= n - 1; ++r) {
            if (rnd.next(5) == 0) continue;
            addZone(zones, n, m, r, blockCol, rnd.next(0, 1));
        }
        int extra = rnd.next(1, 8);
        for (int i = 0; i < extra; ++i) {
            addZone(zones, n, m, rnd.next(1, n), rnd.next(1, m), rnd.next(0, 2));
        }
    } else {
        n = rnd.next(12, 24);
        m = rnd.next(12, 24);
        int k = rnd.next(4, 12);
        for (int i = 0; i < k; ++i) {
            int r = rnd.next(2, n - 1);
            int c = rnd.next(2, m - 1);
            int limit = maxAllowedD(n, m, r, c);
            int d = rnd.next(max(0, limit / 3), min(limit, max(1, limit)));
            zones.emplace_back(r, c, d);
        }
    }

    if (zones.empty()) {
        addZone(zones, n, m, 1, 2, 0);
    }

    shuffle(zones.begin(), zones.end());

    println(n, m);
    println((int)zones.size());
    for (auto [r, c, d] : zones) {
        println(r, c, d);
    }

    return 0;
}
