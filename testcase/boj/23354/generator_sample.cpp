#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, mode == 5 ? 25 : 14);

    vector<vector<int>> grid(n, vector<int>(n, 1));
    int low = rnd.next(1, 12);
    int high = rnd.next(max(low + 1, 20), 1000);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mode == 0) {
                grid[i][j] = rnd.next(1, 30);
            } else if (mode == 1) {
                grid[i][j] = low + (i + j) % rnd.next(2, 7);
            } else if (mode == 2) {
                grid[i][j] = rnd.next(100, 1000);
            } else if (mode == 3) {
                grid[i][j] = rnd.next() < 0.25 ? high : rnd.next(1, 15);
            } else if (mode == 4) {
                grid[i][j] = 1 + abs(i - n / 2) + abs(j - n / 2);
            } else {
                grid[i][j] = rnd.next(1, 1000);
            }
        }
    }

    if (mode == 2 || mode == 3) {
        int row = rnd.next(1, n - 2);
        int gap = rnd.next(0, n - 1);
        for (int j = 0; j < n; ++j) {
            grid[row][j] = j == gap ? low : high;
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    int base_index = 0;
    if (mode == 4) {
        for (int i = 0; i < (int)cells.size(); ++i) {
            if (cells[i] == make_pair(n / 2, n / 2)) {
                base_index = i;
                break;
            }
        }
    }
    swap(cells[0], cells[base_index]);

    int deserters = mode == 0 ? 0 : rnd.next(1, 5);
    if (mode == 5) {
        deserters = 5;
    }

    auto [base_i, base_j] = cells[0];
    grid[base_i][base_j] = -1;
    for (int k = 1; k <= deserters; ++k) {
        auto [i, j] = cells[k];
        grid[i][j] = 0;
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
