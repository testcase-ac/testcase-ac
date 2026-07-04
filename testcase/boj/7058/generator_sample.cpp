#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 12);
    int n = rnd.next(1, 12);
    vector<vector<int>> a(m, vector<int>(n, 0));

    if (mode == 0) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = 0;
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = (i % 2 == 1 || j % 3 == 2) ? 2 : 0;
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int roll = rnd.next(0, 99);
                a[i][j] = roll < 60 ? 1 : (roll < 75 ? 2 : 0);
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = 2;
            }
        }
        int row = rnd.next(0, m - 1);
        int col = rnd.next(0, n - 1);
        for (int j = 0; j < n; ++j) {
            a[row][j] = rnd.next(0, 4) == 0 ? 1 : 0;
        }
        for (int i = 0; i < m; ++i) {
            a[i][col] = rnd.next(0, 4) == 0 ? 1 : 0;
        }
        a[row][col] = 0;
    } else if (mode == 4) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i + j) % 2 == 0) {
                    a[i][j] = 0;
                } else {
                    a[i][j] = rnd.next(0, 1) ? 1 : 2;
                }
            }
        }
    } else {
        int wallChance = rnd.next(5, 45);
        int pitChance = rnd.next(5, 45);
        if (wallChance + pitChance > 80) {
            pitChance = 80 - wallChance;
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int roll = rnd.next(0, 99);
                if (roll < wallChance) {
                    a[i][j] = 2;
                } else if (roll < wallChance + pitChance) {
                    a[i][j] = 1;
                } else {
                    a[i][j] = 0;
                }
            }
        }
    }

    vector<int> cells(m * n);
    for (int i = 0; i < m * n; ++i) {
        cells[i] = i;
    }
    shuffle(cells.begin(), cells.end());
    int tweaks = rnd.next(0, min<int>(6, cells.size()));
    for (int k = 0; k < tweaks; ++k) {
        int i = cells[k] / n;
        int j = cells[k] % n;
        a[i][j] = rnd.next(0, 2);
    }

    println(m, n);
    for (int i = 0; i < m; ++i) {
        println(a[i]);
    }

    return 0;
}
