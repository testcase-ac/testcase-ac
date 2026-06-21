#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> targetRow(int row, int top, int left, int right) {
    vector<vector<int>> p(row + 1);
    p[1] = {top + 1};
    if (row >= 2) {
        p[2] = {left + 1, right + 1};
    }

    for (int i = 3; i <= row; ++i) {
        p[i].assign(i, 0);
        for (int j = 1; j <= i - 2; ++j) {
            p[i][j] = p[i - 1][j - 1] ^ p[i - 1][j];
        }
        p[i][0] = p[i - 1][0] ^ p[i][1];
        p[i][i - 1] = p[i - 1][i - 2] ^ p[i][i - 2];
    }

    vector<int> result = p[row];
    for (int& color : result) {
        --color;
    }
    return result;
}

void printPyramid(const vector<vector<int>>& rows) {
    println(static_cast<int>(rows.size()));
    for (const auto& row : rows) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 5) {
        n = rnd.next(12, 28);
    } else {
        n = rnd.next(3, 12);
    }

    vector<vector<int>> rows(n);
    for (int i = 1; i <= n; ++i) {
        rows[i - 1].resize(i);
    }

    if (mode == 0) {
        int color = rnd.next(0, 2);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                rows[i - 1][j] = (rnd.next(0, 9) == 0 ? rnd.next(0, 2) : color);
            }
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            int a = rnd.next(0, 2);
            int b = rnd.next(0, 2);
            for (int j = 0; j < i; ++j) {
                rows[i - 1][j] = (j % 2 == 0 ? a : b);
            }
            if (rnd.next(0, 2) == 0) {
                shuffle(rows[i - 1].begin(), rows[i - 1].end());
            }
        }
    } else if (mode == 2 || mode == 3) {
        vector<int> base = {0, 1, 2};
        shuffle(base.begin(), base.end());
        rows[0][0] = base[0];
        rows[1][0] = base[1];
        rows[1][1] = base[2];
        for (int i = 3; i <= n; ++i) {
            rows[i - 1] = targetRow(i, rows[0][0], rows[1][0], rows[1][1]);
            if (mode == 3) {
                shuffle(rows[i - 1].begin(), rows[i - 1].end());
            }
        }
    } else if (mode == 4) {
        for (int i = 1; i <= n; ++i) {
            int dominant = rnd.next(0, 2);
            int rare = rnd.next(0, 2);
            for (int j = 0; j < i; ++j) {
                rows[i - 1][j] = dominant;
            }
            int changes = rnd.next(0, min(i, 2));
            for (int k = 0; k < changes; ++k) {
                rows[i - 1][rnd.next(0, i - 1)] = rare;
            }
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            int lo = rnd.next(0, 1);
            int hi = rnd.next(lo, 2);
            for (int j = 0; j < i; ++j) {
                rows[i - 1][j] = rnd.next(lo, hi);
            }
        }
    }

    printPyramid(rows);
    return 0;
}
