#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 5) {
        n = rnd.next(2, 12);
    } else {
        n = rnd.next(13, 25);
    }

    vector<vector<int>> grid(n, vector<int>(n, 0));
    int sr = rnd.next(0, n - 1);
    int sc = rnd.next(0, n - 1);

    if (mode == 1) {
        int legions = rnd.next(0, n * n - 1);
        vector<int> cells;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r != sr || c != sc) cells.push_back(r * n + c);
            }
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < legions; ++i) {
            int id = cells[i];
            grid[id / n][id % n] = 1;
        }
    } else if (mode == 2) {
        int targetParity = rnd.next(0, 1);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if ((r != sr || c != sc) && ((r + c) & 1) == targetParity && rnd.next(0, 99) < 65) {
                    grid[r][c] = 1;
                }
            }
        }
    } else if (mode == 3) {
        int radius = rnd.next(1, max(1, n / 3));
        for (int r = max(0, sr - radius); r <= min(n - 1, sr + radius); ++r) {
            for (int c = max(0, sc - radius); c <= min(n - 1, sc + radius); ++c) {
                if ((r != sr || c != sc) && rnd.next(0, 99) < 70) {
                    grid[r][c] = 1;
                }
            }
        }
    } else if (mode == 4) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == sr && c == sc) continue;
                bool onDiagonal = (r - c == sr - sc) || (r + c == sr + sc);
                if (onDiagonal && rnd.next(0, 99) < 80) {
                    grid[r][c] = 1;
                }
            }
        }
    } else if (mode == 5) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r != sr || c != sc) {
                    grid[r][c] = rnd.next(0, 99) < 12 ? 1 : 0;
                }
            }
        }
    } else if (mode == 6) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r != sr || c != sc) {
                    grid[r][c] = rnd.next(0, 99) < 85 ? 1 : 0;
                }
            }
        }
    }

    grid[sr][sc] = 2;

    println(n);
    for (int r = 0; r < n; ++r) {
        println(grid[r]);
    }

    return 0;
}
