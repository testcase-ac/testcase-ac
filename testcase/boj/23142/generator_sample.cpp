#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<pair<int, int>> rowMajorCells(int n, int m) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cells.push_back({i, j});
        }
    }
    return cells;
}

static vector<pair<int, int>> snakeCells(int n, int m) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; ++j) {
                cells.push_back({i, j});
            }
        } else {
            for (int j = m - 1; j >= 0; --j) {
                cells.push_back({i, j});
            }
        }
    }
    return cells;
}

static vector<pair<int, int>> centerFirstCells(int n, int m) {
    vector<pair<int, int>> cells = rowMajorCells(n, m);
    int centerR2 = n - 1;
    int centerC2 = m - 1;
    sort(cells.begin(), cells.end(), [&](const auto& lhs, const auto& rhs) {
        int lhsDist = abs(2 * lhs.first - centerR2) + abs(2 * lhs.second - centerC2);
        int rhsDist = abs(2 * rhs.first - centerR2) + abs(2 * rhs.second - centerC2);
        if (lhsDist != rhsDist) {
            return lhsDist < rhsDist;
        }
        return lhs < rhs;
    });
    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shapeMode = rnd.next(0, 5);
    int n;
    int m;
    if (shapeMode == 0) {
        n = 1;
        m = rnd.next(2, 18);
    } else if (shapeMode == 1) {
        n = rnd.next(2, 18);
        m = 1;
    } else if (shapeMode <= 3) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (shapeMode == 4) {
        n = rnd.next(2, 5);
        m = rnd.next(9, 20);
    } else {
        n = rnd.next(9, 20);
        m = rnd.next(2, 5);
    }

    int total = n * m;
    vector<pair<int, int>> cells;
    int layoutMode = rnd.next(0, 5);
    if (layoutMode == 0) {
        cells = rowMajorCells(n, m);
    } else if (layoutMode == 1) {
        cells = rowMajorCells(n, m);
        reverse(cells.begin(), cells.end());
    } else if (layoutMode == 2) {
        cells = snakeCells(n, m);
    } else if (layoutMode == 3) {
        cells = centerFirstCells(n, m);
    } else {
        cells = rowMajorCells(n, m);
        shuffle(cells.begin(), cells.end());
    }

    vector<vector<int>> grid(n, vector<int>(m));
    for (int value = 1; value <= total; ++value) {
        auto [r, c] = cells[value - 1];
        grid[r][c] = value;
    }

    if (rnd.next(0, 3) == 0) {
        int swaps = rnd.next(1, min(total, 8));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(total);
            int b = rnd.next(total);
            swap(grid[cells[a].first][cells[a].second], grid[cells[b].first][cells[b].second]);
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
