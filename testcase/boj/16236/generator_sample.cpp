#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5) ? rnd.next(13, 20) : rnd.next(2, 10);
    vector<vector<int>> grid(n, vector<int>(n, 0));

    int sr = rnd.next(n);
    int sc = rnd.next(n);
    grid[sr][sc] = 9;

    vector<pair<int, int>> cells;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r != sr || c != sc) {
                cells.push_back({r, c});
            }
        }
    }
    shuffle(cells.begin(), cells.end());

    if (mode == 0) {
        int fish = rnd.next(0, min<int>(3, cells.size()));
        for (int i = 0; i < fish; ++i) {
            grid[cells[i].first][cells[i].second] = rnd.next(1, 2);
        }
    } else if (mode == 1) {
        for (auto [r, c] : cells) {
            int dist = abs(r - sr) + abs(c - sc);
            if (rnd.next(100) < 45) {
                grid[r][c] = dist <= 2 ? rnd.next(1, 2) : rnd.next(0, 6);
            }
        }
    } else if (mode == 2) {
        for (auto [r, c] : cells) {
            int value = rnd.next(0, 9);
            if (value <= 3) {
                grid[r][c] = 0;
            } else if (value <= 6) {
                grid[r][c] = 1;
            } else {
                grid[r][c] = rnd.next(3, 6);
            }
        }
    } else if (mode == 3) {
        int wallRow = rnd.next(n);
        int gap = rnd.next(n);
        for (int c = 0; c < n; ++c) {
            if (c != gap && grid[wallRow][c] != 9) {
                grid[wallRow][c] = rnd.next(3, 6);
            }
        }
        for (auto [r, c] : cells) {
            if (grid[r][c] == 0 && rnd.next(100) < 35) {
                grid[r][c] = rnd.next(1, 2);
            }
        }
    } else if (mode == 4) {
        int ring = rnd.next(1, max(1, n / 2));
        for (auto [r, c] : cells) {
            int dist = abs(r - sr) + abs(c - sc);
            if (dist == ring) {
                grid[r][c] = 1;
            } else if (dist == ring + 1 && rnd.next(100) < 60) {
                grid[r][c] = 2;
            } else if (rnd.next(100) < 20) {
                grid[r][c] = rnd.next(3, 6);
            }
        }
    } else {
        for (auto [r, c] : cells) {
            int roll = rnd.next(100);
            if (roll < 55) {
                grid[r][c] = 0;
            } else if (roll < 80) {
                grid[r][c] = rnd.next(1, 2);
            } else {
                grid[r][c] = rnd.next(3, 6);
            }
        }
    }

    println(n);
    for (int r = 0; r < n; ++r) {
        println(grid[r]);
    }

    return 0;
}
