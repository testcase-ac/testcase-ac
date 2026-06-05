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
        n = 1;
        m = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 5);
        m = rnd.next(6, 12);
    } else if (mode == 3) {
        n = rnd.next(6, 12);
        m = rnd.next(2, 5);
    } else {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
    }

    vector<pair<int, int>> cells;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    pair<int, int> start = cells[0];
    pair<int, int> finish = cells[1];

    vector<vector<int>> grid(n + 1, vector<int>(m + 1, 0));
    int wallChance;
    if (mode <= 1) {
        wallChance = 0;
    } else if (mode <= 3) {
        wallChance = rnd.next(5, 35);
    } else {
        wallChance = rnd.any(vector<int>{0, 10, 25, 45, 65});
    }

    int maxCost = rnd.any(vector<int>{1, 3, 9, 40, 300});
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (rnd.next(1, 100) <= wallChance) {
                grid[i][j] = -1;
            } else if (rnd.next(0, 5) == 0) {
                grid[i][j] = rnd.next(max(0, maxCost - 5), maxCost);
            } else {
                grid[i][j] = rnd.next(0, maxCost);
            }
        }
    }

    if (mode == 2 || mode == 3) {
        int stripe = rnd.next(1, mode == 2 ? n : m);
        if (mode == 2) {
            for (int j = 1; j <= m; ++j) {
                grid[stripe][j] = rnd.next(0, maxCost);
            }
        } else {
            for (int i = 1; i <= n; ++i) {
                grid[i][stripe] = rnd.next(0, maxCost);
            }
        }
    }

    grid[start.first][start.second] = 0;
    grid[finish.first][finish.second] = 0;

    println(n, m);
    println(start.first, start.second, finish.first, finish.second);
    for (int i = 1; i <= n; ++i) {
        vector<int> row;
        for (int j = 1; j <= m; ++j) {
            row.push_back(grid[i][j]);
        }
        println(row);
    }

    return 0;
}
