#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 12);
    int n = rnd.next(1, 12);
    vector<vector<int>> a(m, vector<int>(n, 1));

    if (mode == 0) {
        int value = rnd.next(1, 10);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = value;
            }
        }
    } else if (mode == 1) {
        vector<int> palette = {1, 2, 3, 4, 5};
        for (int i = 0; i < m; ++i) {
            shuffle(palette.begin(), palette.end());
            for (int j = 0; j < n; ++j) {
                a[i][j] = palette[j % (int)palette.size()];
            }
        }
    } else if (mode == 2) {
        vector<int> palette = {1, 1, 2, 3, 4, 6, 8, 9};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.any(palette);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) {
            int rowBase = rnd.next(1, 5);
            for (int j = 0; j < n; ++j) {
                a[i][j] = rowBase;
            }
            if (n >= 2 && rnd.next(0, 1)) {
                int pos = rnd.next(0, n - 2);
                a[i][pos] = rnd.next(1, 9);
                a[i][pos + 1] = 10 - a[i][pos];
            }
        }
    } else if (mode == 4) {
        for (int j = 0; j < n; ++j) {
            int colBase = rnd.next(1, 5);
            for (int i = 0; i < m; ++i) {
                a[i][j] = colBase;
            }
            if (m >= 2 && rnd.next(0, 1)) {
                int pos = rnd.next(0, m - 2);
                a[pos][j] = rnd.next(1, 9);
                a[pos + 1][j] = 10 - a[pos][j];
            }
        }
    } else {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = rnd.wnext(10, -2) + 1;
            }
        }
    }

    if (rnd.next(0, 4) == 0) {
        m = rnd.next(1, 4);
        n = rnd.next(1, 4);
        a.assign(m, vector<int>(n, 10));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next(0, 2) == 0) {
                    a[i][j] = rnd.next(1, 3);
                }
            }
        }
    }

    println(m, n);
    for (int i = 0; i < m; ++i) {
        println(a[i]);
    }

    return 0;
}
