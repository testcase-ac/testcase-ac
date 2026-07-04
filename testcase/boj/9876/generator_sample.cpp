#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomSnow() {
    return rnd.next(0, 1) == 0 ? 'R' : 'S';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 12);
    int n = rnd.next(1, 12);
    if (mode == 1) {
        m = rnd.next(1, 5);
        n = rnd.next(8, 20);
    } else if (mode == 2) {
        m = rnd.next(8, 20);
        n = rnd.next(1, 5);
    } else if (mode == 5) {
        m = rnd.next(15, 30);
        n = rnd.next(15, 30);
    }

    vector<string> grid(m, string(n, 'R'));

    if (mode == 0) {
        char value = randomSnow();
        for (int i = 0; i < m; ++i) {
            fill(grid[i].begin(), grid[i].end(), value);
        }
    } else if (mode == 1) {
        for (int j = 0; j < n; ++j) {
            char value = (j / rnd.next(1, 3)) % 2 == 0 ? 'R' : 'S';
            for (int i = 0; i < m; ++i) {
                grid[i][j] = value;
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            char value = (i / rnd.next(1, 3)) % 2 == 0 ? 'R' : 'S';
            fill(grid[i].begin(), grid[i].end(), value);
        }
    } else if (mode == 3) {
        int blockH = rnd.next(1, min(4, m));
        int blockW = rnd.next(1, min(4, n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = ((i / blockH + j / blockW) % 2 == 0) ? 'R' : 'S';
            }
        }
    } else if (mode == 4) {
        double roughChance = rnd.next(15, 85) / 100.0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                grid[i][j] = rnd.next() < roughChance ? 'R' : 'S';
            }
        }
    } else {
        int patch = rnd.next(2, 6);
        for (int top = 0; top < m; top += patch) {
            for (int left = 0; left < n; left += patch) {
                char value = randomSnow();
                for (int i = top; i < min(m, top + patch); ++i) {
                    for (int j = left; j < min(n, left + patch); ++j) {
                        grid[i][j] = value;
                    }
                }
            }
        }
    }

    println(m, n);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
