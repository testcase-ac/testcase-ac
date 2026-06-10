#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Segment {
    bool horizontal;
    int row;
    int col;
};

static bool covers(const Segment& segment, int row, int col, int k) {
    if (segment.horizontal) {
        return row == segment.row && segment.col <= col && col < segment.col + k;
    }
    return col == segment.col && segment.row <= row && row < segment.row + k;
}

static bool hasStartInRange(const vector<int>& starts, int low, int high) {
    if (low > high) {
        return false;
    }
    auto it = lower_bound(starts.begin(), starts.end(), low);
    return it != starts.end() && *it <= high;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int k = inf.readInt(1, max(n, m), "K");
    inf.readEoln();

    vector<string> grid(n, string(m, '0'));
    vector<pair<int, int>> ones;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value = inf.readInt(0, 1, "cell");
            grid[i][j] = char('0' + value);
            if (value == 1) {
                ones.push_back({i, j});
            }
            if (j + 1 == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }
    inf.readEof();

    ensuref((int)ones.size() >= k,
            "seed grid has %d occupied cells, but two length-K segments cover at least K cells",
            (int)ones.size());
    ensuref((int)ones.size() <= 2 * k,
            "seed grid has %d occupied cells, but two length-K segments cover at most 2K=%d cells",
            (int)ones.size(), 2 * k);

    vector<Segment> candidates;
    vector<vector<int>> horizontalStarts(n), verticalStarts(m);

    if (k <= m) {
        for (int i = 0; i < n; ++i) {
            int window = 0;
            for (int j = 0; j < m; ++j) {
                window += grid[i][j] == '1';
                if (j >= k) {
                    window -= grid[i][j - k] == '1';
                }
                if (j + 1 >= k && window == k) {
                    int start = j + 1 - k;
                    horizontalStarts[i].push_back(start);
                    candidates.push_back({true, i, start});
                }
            }
        }
    }

    if (k <= n) {
        for (int j = 0; j < m; ++j) {
            int window = 0;
            for (int i = 0; i < n; ++i) {
                window += grid[i][j] == '1';
                if (i >= k) {
                    window -= grid[i - k][j] == '1';
                }
                if (i + 1 >= k && window == k) {
                    int start = i + 1 - k;
                    verticalStarts[j].push_back(start);
                    candidates.push_back({false, start, j});
                }
            }
        }
    }

    bool feasible = false;
    for (const Segment& first : candidates) {
        vector<pair<int, int>> remaining;
        remaining.reserve(ones.size());
        for (auto [row, col] : ones) {
            if (!covers(first, row, col, k)) {
                remaining.push_back({row, col});
            }
        }

        if (remaining.empty()) {
            feasible = true;
            break;
        }
        if ((int)remaining.size() > k) {
            continue;
        }

        bool sameRow = true;
        bool sameCol = true;
        int minRow = remaining[0].first;
        int maxRow = remaining[0].first;
        int minCol = remaining[0].second;
        int maxCol = remaining[0].second;
        for (auto [row, col] : remaining) {
            sameRow &= row == remaining[0].first;
            sameCol &= col == remaining[0].second;
            minRow = min(minRow, row);
            maxRow = max(maxRow, row);
            minCol = min(minCol, col);
            maxCol = max(maxCol, col);
        }

        if (sameRow && maxCol - minCol + 1 <= k) {
            int low = max(0, maxCol - k + 1);
            int high = min(minCol, m - k);
            if (hasStartInRange(horizontalStarts[remaining[0].first], low, high)) {
                feasible = true;
                break;
            }
        }

        if (sameCol && maxRow - minRow + 1 <= k) {
            int low = max(0, maxRow - k + 1);
            int high = min(minRow, n - k);
            if (hasStartInRange(verticalStarts[remaining[0].second], low, high)) {
                feasible = true;
                break;
            }
        }
    }

    ensuref(feasible,
            "seed grid is not the union of two horizontal or vertical length-K segments");
}
