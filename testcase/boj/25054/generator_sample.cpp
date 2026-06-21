#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(2, 3);
    } else {
        n = rnd.next(4, 12);
    }

    vector<vector<int>> a(n, vector<int>(n));
    vector<int> values(n * n);
    iota(values.begin(), values.end(), 1);

    if (mode == 0) {
        shuffle(values.begin(), values.end());
        int at = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = values[at++];
            }
        }
    } else if (mode == 1) {
        int at = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = at++;
            }
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 2) {
        int at = 1;
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                a[i][j] = at++;
            }
        }
        if (rnd.next(0, 1)) {
            for (int i = 0; i < n; ++i) {
                reverse(a[i].begin(), a[i].end());
            }
        }
    } else if (mode == 3) {
        int at = 1;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] = at++;
                }
            } else {
                for (int j = n - 1; j >= 0; --j) {
                    a[i][j] = at++;
                }
            }
        }
    } else if (mode == 4) {
        int lo = 1;
        int hi = n * n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i + j) % 2 == 0) {
                    a[i][j] = lo++;
                } else {
                    a[i][j] = hi--;
                }
            }
        }
    } else {
        int block = rnd.next(1, min(4, n));
        int at = 1;
        for (int rowStart = 0; rowStart < n; rowStart += block) {
            int rowEnd = min(n, rowStart + block);
            vector<pair<int, int>> cells;
            for (int i = rowStart; i < rowEnd; ++i) {
                for (int j = 0; j < n; ++j) {
                    cells.push_back({i, j});
                }
            }
            if (rnd.next(0, 1)) {
                shuffle(cells.begin(), cells.end());
            }
            for (auto [i, j] : cells) {
                a[i][j] = at++;
            }
        }
    }

    if (rnd.next(0, 3) == 0) {
        shuffle(a.begin(), a.end());
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }

    return 0;
}
