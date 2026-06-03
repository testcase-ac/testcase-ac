#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 5);
    } else if (mode == 1) {
        n = rnd.next(5, 10);
        m = rnd.next(5, 10);
    } else if (mode == 2) {
        n = rnd.next(2, 4);
        m = rnd.next(8, 14);
    } else if (mode == 3) {
        n = rnd.next(8, 14);
        m = rnd.next(2, 4);
    } else {
        n = rnd.next(6, 14);
        m = rnd.next(6, 14);
    }

    vector<vector<int>> grid(n, vector<int>(m, 0));

    if (mode == 1) {
        int wallCol = rnd.next(1, m - 2);
        int gap = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i != gap) {
                grid[i][wallCol] = -1;
            }
        }
    } else if (mode == 2) {
        for (int j = 1; j + 1 < m; ++j) {
            if (rnd.next(0, 2) == 0) {
                grid[rnd.next(0, n - 1)][j] = -1;
            }
        }
    } else if (mode == 3) {
        for (int i = 1; i + 1 < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                grid[i][rnd.next(0, m - 1)] = -1;
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j) % 3 == 0 && rnd.next(0, 1) == 0) {
                    grid[i][j] = -1;
                }
            }
        }
    } else if (mode == 5) {
        int obstacleCount = rnd.next(0, max(1, n * m / 4));
        vector<pair<int, int>> cells;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cells.push_back({i, j});
            }
        }
        shuffle(cells.begin(), cells.end());
        for (int k = 0; k < obstacleCount; ++k) {
            grid[cells[k].first][cells[k].second] = -1;
        }
    }

    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 0) {
                emptyCells.push_back({i, j});
            }
        }
    }

    shuffle(emptyCells.begin(), emptyCells.end());
    pair<int, int> first = emptyCells[0];
    pair<int, int> second = emptyCells[1];

    if (mode == 0 && rnd.next(0, 1) == 0) {
        first = {0, 0};
        second = {n - 1, m - 1};
    } else if (mode == 1) {
        first = {rnd.next(0, n - 1), rnd.next(0, max(0, m / 2 - 1))};
        second = {rnd.next(0, n - 1), rnd.next(min(m - 1, m / 2 + 1), m - 1)};
        if (grid[first.first][first.second] == -1 || grid[second.first][second.second] == -1 || first == second) {
            first = emptyCells[0];
            second = emptyCells[1];
        }
    }

    grid[first.first][first.second] = 1;
    grid[second.first][second.second] = 2;

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
