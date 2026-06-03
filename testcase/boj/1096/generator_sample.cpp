#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampCell(int x) {
    return max(-100, min(100, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(8, 12);
        m = rnd.next(8, 12);
    } else if (mode == 2) {
        n = rnd.any(vector<int>{1, 2, 3, 12});
        m = rnd.next(1, 12);
    } else if (mode == 3) {
        n = rnd.next(1, 12);
        m = rnd.any(vector<int>{1, 2, 3, 12});
    }

    vector<vector<int>> a(n, vector<int>(m, 0));
    int base = rnd.next(-8, 8);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value = 0;
            if (mode == 0) {
                value = rnd.next(-5, 5);
            } else if (mode == 1) {
                value = rnd.next(-2, 2);
            } else if (mode == 2) {
                value = (i % 2 == 0 ? 1 : -1) * rnd.next(0, 20);
            } else if (mode == 3) {
                value = (j % 2 == 0 ? 1 : -1) * rnd.next(0, 20);
            } else if (mode == 4) {
                int edge = min(min(i, n - 1 - i), min(j, m - 1 - j));
                value = base + (edge % 2 == 0 ? rnd.next(0, 18) : -rnd.next(0, 18));
            } else if (mode == 5) {
                value = rnd.next(0, 100) < 75 ? -rnd.next(0, 10) : rnd.next(20, 100);
            } else {
                value = ((i + j) % 2 == 0 ? 1 : -1) * rnd.next(0, 30);
            }
            a[i][j] = clampCell(value);
        }
    }

    if (rnd.next(0, 3) == 0) {
        vector<pair<int, int>> cells;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cells.push_back({i, j});
            }
        }
        shuffle(cells.begin(), cells.end());
        int spikes = rnd.next(1, min<int>(4, cells.size()));
        for (int k = 0; k < spikes; ++k) {
            a[cells[k].first][cells[k].second] = rnd.next(0, 1) ? 100 : -100;
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
