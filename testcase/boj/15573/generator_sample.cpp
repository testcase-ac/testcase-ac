#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(3, 8);
        m = rnd.next(3, 8);
    } else if (mode == 3) {
        n = rnd.next(6, 12);
        m = rnd.next(1, 4);
    } else {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
    }

    vector<vector<int>> grid(n, vector<int>(m));
    int low = rnd.next(1, 20);
    int span = rnd.next(0, 80);
    int high = min(1000000, low + span);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next(low, high);
            }
        }
    } else if (mode == 1) {
        int boundary = rnd.next(low, high);
        int insideLow = rnd.next(boundary, min(1000000, boundary + 50));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool exposed = (i == 0 || j == 0 || j == m - 1);
                grid[i][j] = exposed ? rnd.next(low, boundary) : rnd.next(insideLow, min(1000000, insideLow + 200));
            }
        }
    } else if (mode == 2) {
        int wall = rnd.next(500000, 1000000);
        int pocket = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool rim = (i == 0 || j == 0 || j == m - 1);
                bool cross = (i == n / 2 || j == m / 2);
                grid[i][j] = (rim || cross) ? rnd.next(pocket, pocket + 20) : rnd.next(wall - 1000, wall);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = min(1000000, base + i * rnd.next(1, 5) + j * rnd.next(0, 7));
            }
        }
    } else {
        vector<int> values;
        int distinct = rnd.next(2, 6);
        for (int i = 0; i < distinct; ++i) {
            values.push_back(rnd.next(1, 1000000));
        }
        sort(values.begin(), values.end());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.any(values);
            }
        }
    }

    int cells = n * m;
    int kMode = rnd.next(0, 4);
    int k = 1;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = cells;
    } else if (kMode == 2) {
        k = rnd.next(1, min(cells, max(1, m + n)));
    } else {
        k = rnd.next(1, cells);
    }

    println(n, m, k);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
