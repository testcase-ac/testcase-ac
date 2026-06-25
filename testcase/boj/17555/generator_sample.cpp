#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> randomIntervalThrough(int n, int col, int minWidth, int maxWidth) {
    int width = rnd.next(minWidth, maxWidth);
    int lo = max(0, col - width + 1);
    int hi = min(col, n - width);
    int a = rnd.next(lo, hi);
    return {a, a + width - 1};
}

pair<int, int> nextInterval(int n, pair<int, int> prev, int mode) {
    int shared = rnd.next(prev.first, prev.second);
    int maxWidth = n;
    int minWidth = 1;

    if (mode == 0) {
        maxWidth = min(n, max(1, prev.second - prev.first + 1 + rnd.next(0, 3)));
    } else if (mode == 1) {
        minWidth = min(n, max(1, prev.second - prev.first + 1 - rnd.next(0, 2)));
    } else if (mode == 2) {
        maxWidth = min(n, max(1, n / 2 + 1));
    }

    return randomIntervalThrough(n, shared, minWidth, maxWidth);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 9);
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 5) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 35);
    }

    vector<pair<int, int>> rows(n);
    int anchor = rnd.next(0, n - 1);
    rows[anchor] = {0, n - 1};

    int mode = rnd.next(0, 3);
    for (int i = anchor - 1; i >= 0; --i) {
        rows[i] = nextInterval(n, rows[i + 1], mode);
    }
    for (int i = anchor + 1; i < n; ++i) {
        rows[i] = nextInterval(n, rows[i - 1], mode);
    }

    if (mode == 3 && n > 1) {
        int leftBias = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            int width = rows[i].second - rows[i].first + 1;
            int shiftLimit = n - width;
            if (leftBias) {
                rows[i].first = rnd.wnext(shiftLimit + 1, -2);
            } else {
                rows[i].first = rnd.wnext(shiftLimit + 1, 2);
            }
            rows[i].second = rows[i].first + width - 1;
            if (i > 0 && min(rows[i - 1].second, rows[i].second) <
                           max(rows[i - 1].first, rows[i].first)) {
                rows[i] = nextInterval(n, rows[i - 1], 0);
            }
        }
        rows[anchor] = {0, n - 1};
    }

    println(n);
    for (auto row : rows) {
        println(row.first, row.second);
    }

    return 0;
}
