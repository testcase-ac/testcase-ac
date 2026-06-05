#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

int oddInRange(int lo, int hi) {
    if (lo % 2 == 0) ++lo;
    if (hi % 2 == 0) --hi;
    int count = (hi - lo) / 2 + 1;
    return lo + 2 * rnd.next(0, count - 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int r = rnd.next(1, 12);
    int c = rnd.next(1, 12);

    if (mode == 1) {
        r = oddInRange(1, 11);
        c = oddInRange(1, 11);
    } else if (mode == 2) {
        r = rnd.next(2, 12);
        c = rnd.next(2, 12);
    } else if (mode == 6) {
        r = rnd.next(8, 15);
        c = rnd.next(8, 15);
    }

    int h = oddInRange(1, r);
    int w = oddInRange(1, c);
    if (mode == 1) {
        h = r;
        w = c;
    } else if (mode == 2) {
        h = 1;
        w = oddInRange(1, c);
    } else if (mode == 3) {
        h = oddInRange(1, r);
        w = 1;
    } else if (mode == 6) {
        h = min(r, rnd.any(vector<int>{3, 5, 7}));
        if (h % 2 == 0) --h;
        w = min(c, rnd.any(vector<int>{3, 5, 7}));
        if (w % 2 == 0) --w;
    }

    int n = r * c;
    vector<int> values(n);
    iota(values.begin(), values.end(), 1);
    vector<int> grid(n, 0);

    if (mode == 0) {
        shuffle(values.begin(), values.end());
        grid = values;
    } else if (mode == 1) {
        bool descending = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) grid[i] = descending ? n - i : i + 1;
    } else if (mode == 2) {
        bool reverseRows = rnd.next(0, 1);
        bool reverseCols = rnd.next(0, 1);
        for (int i = 0; i < r; ++i) {
            int row = reverseRows ? r - 1 - i : i;
            for (int j = 0; j < c; ++j) {
                int col = reverseCols ? c - 1 - j : j;
                grid[row * c + col] = i * c + j + 1;
            }
        }
    } else if (mode == 3) {
        bool descending = rnd.next(0, 1);
        for (int j = 0; j < c; ++j) {
            for (int i = 0; i < r; ++i) {
                int rank = j * r + i + 1;
                grid[i * c + j] = descending ? n - rank + 1 : rank;
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int k = i * c + j;
                int col = (i % 2 == 0) ? j : c - 1 - j;
                grid[i * c + col] = k + 1;
            }
        }
        if (rnd.next(0, 1)) {
            for (int& x : grid) x = n - x + 1;
        }
    } else {
        vector<tuple<int, int, int>> cells;
        int centerR = rnd.next(0, r - 1);
        int centerC = rnd.next(0, c - 1);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int distance = abs(i - centerR) + abs(j - centerC);
                if (mode == 6) distance += rnd.next(0, 2);
                cells.emplace_back(distance, rnd.next(0, 1000000), i * c + j);
            }
        }
        sort(cells.begin(), cells.end());
        if (mode == 7) reverse(cells.begin(), cells.end());
        for (int rank = 1; rank <= n; ++rank) {
            grid[get<2>(cells[rank - 1])] = rank;
        }
    }

    println(r, c, h, w);
    for (int i = 0; i < r; ++i) {
        vector<int> row;
        for (int j = 0; j < c; ++j) row.push_back(grid[i * c + j]);
        println(row);
    }

    return 0;
}
