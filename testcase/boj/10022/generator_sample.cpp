#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int chooseK(int n, int mode) {
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(0, min(3, 2 * n));
    if (mode == 2) return n;
    if (mode == 3) return 2 * n;
    return rnd.next(0, 2 * n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 5) {
        n = rnd.next(18, 35);
    } else {
        n = rnd.next(6, 14);
    }

    int k = chooseK(n, rnd.next(0, 4));
    vector<vector<int>> grid(n, vector<int>(n, 0));

    if (mode == 0) {
        grid[0][0] = rnd.next(0, 1000);
    } else if (mode == 1) {
        int base = rnd.next(0, 20);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = base + rnd.next(0, 30);
            }
        }
    } else if (mode == 2) {
        int spikes = rnd.next(1, max(1, n));
        for (int i = 0; i < spikes; ++i) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, n - 1);
            grid[r][c] = rnd.next(700, 1000);
        }
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 0 && rnd.next(0, 9) == 0) {
                    grid[r][c] = rnd.next(1, 50);
                }
            }
        }
    } else if (mode == 3) {
        int rowWeight = rnd.next(1, 20);
        int colWeight = rnd.next(1, 20);
        int offset = rnd.next(0, 100);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = min(1000, offset + rowWeight * r + colWeight * c + rnd.next(0, 15));
            }
        }
    } else if (mode == 4) {
        int high = rnd.next(600, 1000);
        int low = rnd.next(0, 50);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if ((r + c + rnd.next(0, 1)) % 3 == 0) {
                    grid[r][c] = high - rnd.next(0, 120);
                } else {
                    grid[r][c] = low + rnd.next(0, 30);
                }
            }
        }
    } else {
        int cap = rnd.next(50, 1000);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = rnd.next(0, cap);
            }
        }
    }

    println(n, k);
    for (int r = 0; r < n; ++r) {
        println(grid[r]);
    }

    return 0;
}
