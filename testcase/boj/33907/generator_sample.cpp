#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int randomRisk(int style) {
    if (style == 0) {
        return rnd.next(0, 9);
    }
    if (style == 1) {
        return rnd.any(vector<int>{0, 1, 2, 10, 100, 1000});
    }
    if (style == 2) {
        return rnd.next(0, 1000000000);
    }
    return rnd.wnext(1000000001, 3);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 9);
    int m = rnd.next(2, 9);
    int maxK = min(1400, n + m + rnd.next(0, n * m));
    int k = rnd.next(0, maxK);

    vector<vector<int>> grid(n, vector<int>(m));
    int style = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = randomRisk(style);
        }
    }
    grid[0][0] = 0;

    if (mode == 0) {
        int wall = rnd.next(10, 1000);
        int gap = rnd.next(1, m - 1);
        for (int j = 0; j < m; ++j) {
            grid[n / 2][j] = wall;
        }
        grid[n / 2][gap] = rnd.next(0, 3);
    } else if (mode == 1) {
        int low = rnd.next(0, 5);
        int high = rnd.next(50, 1000000000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = ((i + j) % 2 == 0 ? low : high);
            }
        }
        grid[0][0] = 0;
    } else if (mode == 2) {
        int trail = rnd.next(0, 4);
        int blocked = rnd.next(100, 1000000000);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = blocked;
            }
        }
        for (int i = 0; i < n; ++i) {
            grid[i][0] = trail + rnd.next(0, 2);
        }
        for (int j = 0; j < m; ++j) {
            grid[n - 1][j] = trail + rnd.next(0, 2);
        }
        grid[0][0] = 0;
    } else if (mode == 3) {
        int threshold = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = threshold + rnd.next(-1, 1);
            }
        }
        grid[0][0] = 0;
    } else if (mode == 4) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
        k = rnd.any(vector<int>{0, 1, 2, 1400});
        grid.assign(n, vector<int>(m, rnd.next(0, 2)));
        grid[0][0] = 0;
        grid[n - 1][m - 1] = rnd.next(0, 1000000000);
    } else {
        k = rnd.any(vector<int>{0, 1, min(1400, n * m / 2), 1400});
    }

    println(n, m, k);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
