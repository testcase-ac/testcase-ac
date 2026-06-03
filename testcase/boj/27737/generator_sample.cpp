#include "testlib.h"
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int countRequiredSpores(const vector<vector<int>>& grid, int k) {
    int n = static_cast<int>(grid.size());
    vector<vector<int>> seen(n, vector<int>(n));
    int total = 0;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] == 1 || seen[r][c]) {
                continue;
            }
            int cells = 0;
            queue<pair<int, int>> q;
            q.push({r, c});
            seen[r][c] = 1;
            while (!q.empty()) {
                auto [cr, cc] = q.front();
                q.pop();
                ++cells;
                for (int d = 0; d < 4; ++d) {
                    int nr = cr + dr[d];
                    int nc = cc + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                        continue;
                    }
                    if (grid[nr][nc] == 1 || seen[nr][nc]) {
                        continue;
                    }
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
            total += (cells + k - 1) / k;
        }
    }
    return total;
}

int pickM(int need) {
    int mode = rnd.next(6);
    if (mode == 0) {
        return 0;
    }
    if (mode == 1) {
        return max(0, need - rnd.next(1, 3));
    }
    if (mode == 2) {
        return need;
    }
    if (mode == 3) {
        return min(1000000, need + rnd.next(1, 20));
    }
    if (mode == 4) {
        return rnd.next(0, 20);
    }
    return rnd.next(999980, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(1, 12);
    if (mode == 7) {
        n = rnd.next(15, 30);
    }

    vector<vector<int>> grid(n, vector<int>(n, 1));
    int k = rnd.next(1, 12);

    if (mode == 0) {
        k = rnd.any(vector<int>{1, rnd.next(2, 12), 100000000});
    } else if (mode == 1) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = 0;
            }
        }
        k = rnd.any(vector<int>{1, rnd.next(2, max(2, n)), rnd.next(n * n, 100000000)});
    } else if (mode == 2) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = (r + c) % 2;
            }
        }
        k = rnd.next(1, 5);
    } else if (mode == 3) {
        int row = rnd.next(n);
        int col = rnd.next(n);
        for (int c = 0; c < n; ++c) {
            grid[row][c] = 0;
        }
        for (int r = 0; r < n; ++r) {
            grid[r][col] = 0;
        }
        k = rnd.next(1, max(1, 2 * n - 1));
    } else if (mode == 4) {
        int cells = rnd.next(1, n * n);
        for (int i = 0; i < cells; ++i) {
            int r = i / n;
            int c = (r % 2 == 0) ? (i % n) : (n - 1 - i % n);
            grid[r][c] = 0;
        }
        k = rnd.next(1, max(1, cells));
    } else if (mode == 5) {
        double growableProb = rnd.next(0.20, 0.75);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = rnd.next() < growableProb ? 0 : 1;
            }
        }
        k = rnd.next(1, 20);
    } else if (mode == 6) {
        int blocks = rnd.next(1, min(n, 5));
        for (int b = 0; b < blocks; ++b) {
            int h = rnd.next(1, max(1, n / 2));
            int w = rnd.next(1, max(1, n / 2));
            int sr = rnd.next(0, n - h);
            int sc = rnd.next(0, n - w);
            for (int r = sr; r < sr + h; ++r) {
                for (int c = sc; c < sc + w; ++c) {
                    grid[r][c] = 0;
                }
            }
        }
        k = rnd.next(1, 30);
    } else {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                grid[r][c] = rnd.next(100) < 35 ? 1 : 0;
            }
        }
        k = rnd.any(vector<int>{1, 2, 3, 10, 100000000});
    }

    int need = countRequiredSpores(grid, k);
    int m = pickM(need);

    println(n, m, k);
    for (int r = 0; r < n; ++r) {
        println(grid[r]);
    }

    return 0;
}
