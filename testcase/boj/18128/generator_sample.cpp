#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 18);
    if (mode == 1) {
        n = rnd.next(3, 28);
    } else if (mode == 5) {
        n = rnd.next(20, 45);
    }

    vector<string> grid(n, string(n, '0'));

    if (mode == 0) {
        double density = rnd.next(0.45, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.next() < density ? '1' : '0';
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = '1';
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            grid[i][i] = '1';
            if (i + 1 < n && rnd.next(0, 1) == 1) {
                grid[i][i + 1] = '1';
            }
            if (i > 0 && rnd.next(0, 1) == 1) {
                grid[i][i - 1] = '1';
            }
        }
        int extras = rnd.next(0, n);
        while (extras--) {
            grid[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = '1';
        }
    } else if (mode == 3) {
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, n - 1);
        for (int j = 0; j < n; ++j) {
            grid[row][j] = '1';
        }
        for (int i = 0; i < n; ++i) {
            grid[i][col] = '1';
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                grid[i][rnd.next(0, n - 1)] = '1';
            }
        }
    } else if (mode == 4) {
        int clusterSize = rnd.next(1, min(4, n - 1));
        for (int i = 0; i < clusterSize; ++i) {
            for (int j = 0; j < clusterSize; ++j) {
                grid[i][j] = '1';
                grid[n - 1 - i][n - 1 - j] = '1';
            }
        }
        int extras = rnd.next(0, n / 2);
        while (extras--) {
            grid[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = '1';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.next(0, 9) == 0 ? '1' : '0';
            }
        }
        for (int i = 0; i < n; ++i) {
            grid[i][i] = '1';
        }
    }

    grid[0][0] = '1';
    grid[n - 1][n - 1] = '1';

    int w = rnd.next(1, n);
    vector<pair<int, int>> water;
    water.reserve(w);
    for (int i = 0; i < w; ++i) {
        if (mode == 5 && i > 0 && rnd.next(0, 2) == 0) {
            water.push_back(water[rnd.next(0, (int)water.size() - 1)]);
        } else if (mode == 3 && rnd.next(0, 1) == 0) {
            water.emplace_back(rnd.next(1, n), rnd.next(1, n));
        } else {
            water.emplace_back(rnd.next(1, n), rnd.next(1, n));
        }
    }

    println(n, w);
    for (auto [x, y] : water) {
        println(x, y);
    }
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
