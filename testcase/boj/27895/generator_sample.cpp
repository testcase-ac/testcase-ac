#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    if (mode == 1) {
        n = rnd.next(1, 4);
        m = rnd.next(8, 14);
    } else if (mode == 2) {
        n = rnd.next(8, 14);
        m = rnd.next(1, 4);
    } else if (mode == 3) {
        n = rnd.next(2, 7);
        m = rnd.next(2, 7);
    }

    vector<string> grid(m, string(n, '0'));
    vector<pair<int, int>> cells;
    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            if ((x == 0 && y == 0) || (x == n - 1 && y == m - 1)) {
                continue;
            }
            cells.push_back({x, y});
        }
    }
    shuffle(cells.begin(), cells.end());

    int maxPairs = (int)cells.size() / 2;
    int k = 0;
    if (maxPairs > 0) {
        if (mode == 0) {
            k = 0;
        } else if (mode == 4) {
            k = rnd.next(max(0, maxPairs - 3), maxPairs);
        } else {
            k = rnd.next(0, min(maxPairs, rnd.next(1, 8)));
        }
    }

    int portalCells = 2 * k;
    for (int i = 0; i < portalCells; ++i) {
        auto [x, y] = cells[i];
        grid[y][x] = 'P';
    }

    int wallStart = portalCells;
    int remaining = (int)cells.size() - wallStart;
    int wallCount = 0;
    if (remaining > 0 && mode != 4) {
        int limit = min(remaining, rnd.next(0, max(0, min(remaining, 18))));
        if (mode == 0) {
            limit = rnd.next(0, min(remaining, 10));
        } else if (mode == 5) {
            limit = rnd.next(remaining / 3, remaining);
        }
        wallCount = limit;
    }
    for (int i = 0; i < wallCount; ++i) {
        auto [x, y] = cells[wallStart + i];
        grid[y][x] = '1';
    }

    vector<pair<int, int>> portals(cells.begin(), cells.begin() + portalCells);
    if (mode == 3) {
        sort(portals.begin(), portals.end(), [](const auto& a, const auto& b) {
            return a.first + a.second < b.first + b.second;
        });
    } else {
        shuffle(portals.begin(), portals.end());
    }

    println(n, m, k);
    for (const string& row : grid) {
        println(row);
    }
    for (int i = 0; i < k; ++i) {
        auto a = portals[i];
        auto b = portals[portalCells - 1 - i];
        println(a.first, a.second, b.first, b.second);
    }

    return 0;
}
