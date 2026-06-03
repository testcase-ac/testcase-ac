#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;
    int q = 1;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 10);
        q = rnd.next(m, min(30, 4 * m + 6));
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        m = 1;
        q = rnd.next(n, min(30, 4 * n + 6));
    } else if (mode == 2) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
        q = rnd.next(n + m, min(45, 3 * n * m + 8));
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
        q = rnd.next(n * m, min(70, 4 * n * m));
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
        q = rnd.next(40, 120);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        q = rnd.next(1, 80);
    }

    vector<vector<int>> height(n, vector<int>(m));
    int heightMode = rnd.next(0, 3);
    int base = rnd.next(0, 1000);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (heightMode == 0) {
                height[i][j] = rnd.next(0, 20);
            } else if (heightMode == 1) {
                height[i][j] = base;
            } else if (heightMode == 2) {
                height[i][j] = (i + j) % 2 == 0 ? rnd.next(0, 5) : rnd.next(995, 1000);
            } else {
                height[i][j] = rnd.next(0, 1000);
            }
        }
    }

    vector<pair<int, int>> cells;
    cells.reserve(n * m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cells.emplace_back(i, j);
        }
    }
    shuffle(cells.begin(), cells.end());

    vector<pair<int, int>> queryCells;
    queryCells.reserve(q);

    if (mode == 2 || mode == 3) {
        int take = min<int>(cells.size(), q);
        for (int i = 0; i < take; ++i) {
            queryCells.push_back(cells[i]);
        }
    }

    while ((int)queryCells.size() < q) {
        if (!queryCells.empty() && rnd.next(0, 99) < 45) {
            queryCells.push_back(rnd.any(queryCells));
            continue;
        }

        if (mode <= 1 || rnd.next(0, 99) < 45) {
            queryCells.push_back(rnd.any(cells));
        } else {
            int centerRow = rnd.next(1, n);
            int centerCol = rnd.next(1, m);
            int row = min(n, max(1, centerRow + rnd.next(-1, 1)));
            int col = min(m, max(1, centerCol + rnd.next(-1, 1)));
            queryCells.emplace_back(row, col);
        }
    }

    println(n, m, q);
    for (int i = 0; i < n; ++i) {
        println(height[i]);
    }
    for (auto [row, col] : queryCells) {
        int c = rnd.next(1, 100);
        if (rnd.next(0, 99) < 25) {
            c = rnd.next(1, 5);
        }
        println(row, col, c);
    }

    return 0;
}
