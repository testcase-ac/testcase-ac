#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> sizes = {2, 4, 6, 8, 10, 12};
    int n = rnd.any(sizes);
    int mode = rnd.next(0, 5);

    vector<vector<int>> grid(n, vector<int>(n));
    vector<int> values(n * n);
    for (int i = 0; i < n * n; ++i) {
        values[i] = i + 1;
    }

    if (mode == 0) {
        shuffle(values.begin(), values.end());
        for (int i = 0, p = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = values[p++];
            }
        }
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 1) {
            reverse(values.begin(), values.end());
        }
        for (int i = 0, p = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = values[p++];
            }
        }
    } else if (mode == 2) {
        if (rnd.next(0, 1) == 1) {
            reverse(values.begin(), values.end());
        }
        for (int j = 0, p = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                grid[i][j] = values[p++];
            }
        }
    } else if (mode == 3) {
        int lo = 1;
        int hi = n * n;
        for (int parity = 0; parity < 2; ++parity) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if ((i + j) % 2 == parity) {
                        grid[i][j] = (parity == 0 ? lo++ : hi--);
                    }
                }
            }
        }
    } else {
        int p = 0;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                for (int j = 0; j < n; ++j) {
                    grid[i][j] = values[p++];
                }
            } else {
                for (int j = n - 1; j >= 0; --j) {
                    grid[i][j] = values[p++];
                }
            }
        }
    }

    int swaps = rnd.next(0, n);
    for (int s = 0; s < swaps; ++s) {
        int r1 = rnd.next(0, n - 1);
        int c1 = rnd.next(0, n - 1);
        int r2 = rnd.next(0, n - 1);
        int c2 = rnd.next(0, n - 1);
        swap(grid[r1][c1], grid[r2][c2]);
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(grid[i]);
    }

    return 0;
}
