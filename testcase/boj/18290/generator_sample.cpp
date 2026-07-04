#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

static bool nonAdjacent(const vector<pair<int, int>>& cells) {
    for (int i = 0; i < (int)cells.size(); ++i) {
        for (int j = i + 1; j < (int)cells.size(); ++j) {
            if (abs(cells[i].first - cells[j].first) + abs(cells[i].second - cells[j].second) == 1) {
                return false;
            }
        }
    }
    return true;
}

static int maxSelectable(int n, int m) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.push_back({i, j});
        }
    }

    int total = n * m;
    int best = 1;
    for (int k = 1; k <= min(4, total); ++k) {
        vector<bool> selected(total, false);
        fill(selected.begin(), selected.begin() + k, true);
        bool possible = false;
        do {
            vector<pair<int, int>> chosen;
            for (int i = 0; i < total; ++i) {
                if (selected[i]) {
                    chosen.push_back(cells[i]);
                }
            }
            if (nonAdjacent(chosen)) {
                possible = true;
                break;
            }
        } while (prev_permutation(selected.begin(), selected.end()));

        if (possible) {
            best = k;
        }
    }
    return best;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            n = 1;
            m = rnd.next(1, 10);
        } else {
            n = rnd.next(1, 10);
            m = 1;
        }
    } else if (mode == 2) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
    } else {
        n = rnd.next(3, 10);
        m = rnd.next(3, 10);
    }

    int k = rnd.next(1, maxSelectable(n, m));
    println(n, m, k);

    int low = -10;
    int high = 10;
    if (mode == 3) {
        low = -10000;
        high = 10000;
    } else if (mode == 4) {
        low = -10000;
        high = 20;
    } else if (mode == 5) {
        low = -20;
        high = 10000;
    }

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value = rnd.next(low, high);
            if (mode == 2) {
                value = ((i + j) % 2 == 0) ? rnd.next(3, 25) : rnd.next(-25, 3);
            }
            grid[i][j] = value;
        }
    }

    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
