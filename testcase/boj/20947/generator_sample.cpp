#include "testlib.h"

#include <string>
#include <utility>
#include <vector>
using namespace std;

bool validGrid(const vector<string>& grid) {
    int n = (int)grid.size();
    vector<vector<char>> unsafe(n, vector<char>(n, 0));

    for (int i = 0; i < n; ++i) {
        char last = 0;
        for (int j = 0; j < n; ++j) {
            if (last == 'O') unsafe[i][j] = 1;
            if (grid[i][j] != '.') last = grid[i][j];
        }

        last = 0;
        for (int j = n - 1; j >= 0; --j) {
            if (last == 'O') unsafe[i][j] = 1;
            if (grid[i][j] != '.') last = grid[i][j];
        }
    }

    for (int j = 0; j < n; ++j) {
        char last = 0;
        for (int i = 0; i < n; ++i) {
            if (last == 'O') unsafe[i][j] = 1;
            if (grid[i][j] != '.') last = grid[i][j];
        }

        last = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (last == 'O') unsafe[i][j] = 1;
            if (grid[i][j] != '.') last = grid[i][j];
        }
    }

    vector<vector<char>> destroyed(n, vector<char>(n, 0));
    const int di[4] = {-1, 1, 0, 0};
    const int dj[4] = {0, 0, -1, 1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] != '.' || unsafe[i][j]) continue;

            for (int dir = 0; dir < 4; ++dir) {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                while (0 <= ni && ni < n && 0 <= nj && nj < n && grid[ni][nj] == '.') {
                    ni += di[dir];
                    nj += dj[dir];
                }
                if (0 <= ni && ni < n && 0 <= nj && nj < n && grid[ni][nj] == 'X') {
                    destroyed[ni][nj] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'X' && !destroyed[i][j]) return false;
        }
    }
    return true;
}

void placeRandomBuildings(vector<string>& grid, int tries) {
    int n = (int)grid.size();
    for (int it = 0; it < tries; ++it) {
        int i = rnd.next(n);
        int j = rnd.next(n);
        if (grid[i][j] == '.') grid[i][j] = 'O';
    }
}

void placeBombRays(vector<string>& grid, int bombCount, bool adjacentOnly) {
    int n = (int)grid.size();
    const int di[4] = {-1, 1, 0, 0};
    const int dj[4] = {0, 0, -1, 1};

    for (int b = 0; b < bombCount; ++b) {
        int i = rnd.next(n);
        int j = rnd.next(n);
        if (grid[i][j] != '.') continue;

        vector<int> dirs = {0, 1, 2, 3};
        shuffle(dirs.begin(), dirs.end());
        int used = rnd.next(1, 4);
        for (int t = 0; t < used; ++t) {
            int dir = dirs[t];
            int limit = 0;
            int ni = i + di[dir];
            int nj = j + dj[dir];
            while (0 <= ni && ni < n && 0 <= nj && nj < n && grid[ni][nj] == '.') {
                ++limit;
                ni += di[dir];
                nj += dj[dir];
            }
            if (limit == 0) continue;

            int dist = adjacentOnly ? 1 : rnd.next(1, limit);
            int xi = i + di[dir] * dist;
            int xj = j + dj[dir] * dist;
            grid[xi][xj] = 'X';

            int oi = xi + di[dir];
            int oj = xj + dj[dir];
            if (0 <= oi && oi < n && 0 <= oj && oj < n && grid[oi][oj] == '.' && rnd.next(2) == 0) {
                grid[oi][oj] = 'O';
            }
        }
    }
}

vector<string> makeCandidate() {
    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(5, 18);
    }

    vector<string> grid(n, string(n, '.'));

    if (mode == 0) {
        if (n > 1 && rnd.next(2) == 0) grid[rnd.next(n)][rnd.next(n)] = 'X';
        return grid;
    }

    if (mode == 2 || mode == 4) {
        placeRandomBuildings(grid, rnd.next(1, n));
    }

    int bombCount = rnd.next(1, max(1, n * n / 5));
    placeBombRays(grid, bombCount, mode == 1);

    if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(3) == 0) grid[i][0] = 'O';
            if (rnd.next(3) == 0) grid[i][n - 1] = 'O';
            if (rnd.next(3) == 0) grid[0][i] = 'O';
            if (rnd.next(3) == 0) grid[n - 1][i] = 'O';
        }
    }

    return grid;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> grid;
    for (int attempt = 0; attempt < 10000; ++attempt) {
        grid = makeCandidate();
        if (validGrid(grid)) break;
    }

    if (!validGrid(grid)) {
        grid = vector<string>(1, ".");
    }

    println((int)grid.size());
    for (const string& row : grid) println(row);
    return 0;
}
