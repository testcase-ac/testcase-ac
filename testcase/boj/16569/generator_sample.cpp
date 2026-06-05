#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m;
    int n;
    if (mode == 0) {
        m = rnd.next(1, 2);
        n = rnd.next(2, 4);
    } else if (mode == 1) {
        m = rnd.next(2, 4);
        n = rnd.next(1, 2);
    } else if (mode == 2) {
        m = rnd.next(3, 6);
        n = rnd.next(3, 6);
    } else if (mode == 3) {
        m = rnd.next(6, 10);
        n = rnd.next(6, 10);
    } else if (mode == 4) {
        m = rnd.next(1, 3);
        n = rnd.next(8, 14);
    } else {
        m = rnd.next(8, 14);
        n = rnd.next(1, 3);
    }
    if (m * n == 1) {
        n = 2;
    }

    int startX = rnd.next(1, m);
    int startY = rnd.next(1, n);

    vector<vector<int>> h(m, vector<int>(n));
    int heightMode = rnd.next(0, 3);
    int base = rnd.next(0, 80);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (heightMode == 0) {
                h[i][j] = rnd.next(0, 100);
            } else if (heightMode == 1) {
                h[i][j] = base + 3 * i + 5 * j + rnd.next(0, 7);
            } else if (heightMode == 2) {
                h[i][j] = rnd.next(0, 4) == 0 ? rnd.next(9000, 10000) : rnd.next(0, 50);
            } else {
                h[i][j] = (abs(i + 1 - startX) + abs(j + 1 - startY)) * rnd.next(4, 20);
            }
            h[i][j] = min(h[i][j], 10000);
        }
    }
    h[startX - 1][startY - 1] = rnd.next(0, 10000);

    vector<pair<int, int>> cells;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != startX || j != startY) {
                cells.push_back({i, j});
            }
        }
    }
    shuffle(cells.begin(), cells.end());

    int maxV = (int)cells.size();
    int v;
    if (mode <= 1) {
        v = rnd.next(1, maxV);
    } else if (mode == 3) {
        v = rnd.next(max(1, maxV / 3), maxV);
    } else {
        v = rnd.next(1, min(maxV, max(2, m + n)));
    }

    vector<int> times(v);
    for (int i = 0; i < v; ++i) {
        if (mode == 0 || mode == 1) {
            times[i] = rnd.next(0, 8);
        } else if (mode == 3) {
            times[i] = rnd.next(0, 20);
        } else if (mode == 4 || mode == 5) {
            times[i] = rnd.next(0, 1) ? rnd.next(0, 5) : rnd.next(50, 200);
        } else {
            times[i] = rnd.next(0, 200);
        }
    }

    println(m, n, v);
    println(startX, startY);
    for (int i = 0; i < m; ++i) {
        println(h[i]);
    }
    for (int i = 0; i < v; ++i) {
        println(cells[i].first, cells[i].second, times[i]);
    }

    return 0;
}
