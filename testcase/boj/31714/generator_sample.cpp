#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

void printCase(int n, int m, int d, const vector<vector<int>>& h) {
    println(n, m, d);
    for (int i = 0; i < n; ++i) {
        println(h[i]);
    }
}

vector<vector<int>> makeRandomHeights(int n, int m, int lo, int hi) {
    vector<vector<int>> h(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            h[i][j] = rnd.next(lo, hi);
        }
    }
    return h;
}

vector<vector<int>> makeLikelyYesHeights(int n, int m, int d) {
    vector<vector<int>> h(n, vector<int>(m));
    vector<int> adjusted(m);
    int firstMax = max(1, 100000 - d * (n - 1) - 4 * n);
    for (int j = 0; j < m; ++j) {
        adjusted[j] = rnd.next(1, firstMax);
    }
    sort(adjusted.begin(), adjusted.end());

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            for (int j = 0; j < m; ++j) {
                adjusted[j] += rnd.next(1, 4);
            }
            sort(adjusted.begin(), adjusted.end());
        }
        for (int j = 0; j < m; ++j) {
            h[i][j] = adjusted[j] - d * i;
        }
        shuffle(h[i].begin(), h[i].end());
    }
    return h;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 12);
    int d = rnd.next(1, 20);
    vector<vector<int>> h;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 3);
        d = rnd.any(vector<int>{1, 100000});
        h = makeRandomHeights(n, m, 1, 100000);
    } else if (mode == 1) {
        h = makeLikelyYesHeights(n, m, d);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(1, 10);
        d = rnd.next(1, 15);
        h = makeLikelyYesHeights(n, m, d);
        int row = rnd.next(1, n - 1);
        int col = rnd.next(0, m - 1);
        int frontAdjusted = h[row - 1][col] + d * (row - 1);
        h[row][rnd.next(0, m - 1)] = max(1, frontAdjusted - d * row - rnd.next(0, 2));
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        m = rnd.next(1, 12);
        d = rnd.next(1, 8);
        int base = rnd.next(1, 30);
        h.assign(n, vector<int>(m, base));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                h[i][j] += rnd.next(0, 3);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 8);
        m = rnd.next(6, 14);
        d = rnd.next(1, 25);
        h = makeRandomHeights(n, m, 1, 60);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        d = rnd.next(1, 100000);
        h = makeRandomHeights(n, m, 1, 100000);
    }

    printCase(n, m, d, h);
    return 0;
}
