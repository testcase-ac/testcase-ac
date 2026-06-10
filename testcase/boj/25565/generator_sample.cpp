#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct Segment {
    bool horizontal;
    int row;
    int col;
};

static vector<Segment> allSegments(int n, int m, int k) {
    vector<Segment> segments;
    if (k <= m) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j + k <= m; ++j) {
                segments.push_back({true, i, j});
            }
        }
    }
    if (k <= n) {
        for (int i = 0; i + k <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                segments.push_back({false, i, j});
            }
        }
    }
    return segments;
}

static void paint(vector<vector<int>>& grid, const Segment& segment, int k) {
    for (int d = 0; d < k; ++d) {
        int row = segment.row + (segment.horizontal ? 0 : d);
        int col = segment.col + (segment.horizontal ? d : 0);
        grid[row][col] = 1;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n = 1;
    int m = 1;
    int k = 1;
    Segment first{true, 0, 0};
    Segment second{true, 0, 0};

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
        k = 1;
        auto segments = allSegments(n, m, k);
        first = rnd.any(segments);
        second = rnd.any(segments);
    } else if (mode == 1) {
        n = rnd.next(1, 6);
        m = rnd.next(2, 10);
        k = rnd.next(2, m);
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, m - k);
        first = {true, row, col};
        second = first;
    } else if (mode == 2) {
        n = rnd.next(1, 6);
        m = rnd.next(3, 12);
        k = rnd.next(2, min(7, m));
        int row = rnd.next(0, n - 1);
        int left = rnd.next(0, m - k);
        int low = max(0, left - k + 1);
        int high = min(m - k, left + k - 1);
        int right = rnd.next(low, high);
        first = {true, row, left};
        second = {true, row, right};
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        m = rnd.next(1, 6);
        k = rnd.next(2, min(7, n));
        int col = rnd.next(0, m - 1);
        int top = rnd.next(0, n - k);
        int low = max(0, top - k + 1);
        int high = min(n - k, top + k - 1);
        int bottom = rnd.next(low, high);
        first = {false, top, col};
        second = {false, bottom, col};
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
        k = rnd.next(1, min(n, m));
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, m - 1);
        int hStart = rnd.next(max(0, col - k + 1), min(col, m - k));
        int vStart = rnd.next(max(0, row - k + 1), min(row, n - k));
        first = {true, row, hStart};
        second = {false, vStart, col};
    } else if (mode == 5) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
        k = rnd.next(1, max(n, m));
        auto segments = allSegments(n, m, k);
        first = rnd.any(segments);
        second = rnd.any(segments);
    } else if (mode == 6) {
        n = rnd.next(1, 3);
        m = rnd.next(7, 14);
        k = rnd.next(n + 1, m);
        auto segments = allSegments(n, m, k);
        first = rnd.any(segments);
        second = rnd.any(segments);
    } else if (mode == 7) {
        n = rnd.next(7, 14);
        m = rnd.next(1, 3);
        k = rnd.next(m + 1, n);
        auto segments = allSegments(n, m, k);
        first = rnd.any(segments);
        second = rnd.any(segments);
    } else {
        n = rnd.next(4, 12);
        m = rnd.next(4, 12);
        k = rnd.next(1, min(n, m));
        auto segments = allSegments(n, m, k);
        shuffle(segments.begin(), segments.end());
        first = segments[0];
        second = segments[1];
    }

    vector<vector<int>> grid(n, vector<int>(m, 0));
    paint(grid, first, k);
    paint(grid, second, k);

    println(n, m, k);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
