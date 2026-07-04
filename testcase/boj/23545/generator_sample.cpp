#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 14);
    int m = rnd.next(1, 18);
    vector<string> grid(n, string(m, '.'));

    if (mode == 0) {
        double wallProb = rnd.next(0.0, 0.75);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (rnd.next() < wallProb) grid[i][j] = '#';
    } else if (mode == 1) {
        char fillChar = rnd.next(0, 1) == 0 ? '.' : '#';
        for (int i = 0; i < n; ++i)
            fill(grid[i].begin(), grid[i].end(), fillChar);
        if (fillChar == '#' && rnd.next(0, 2) == 0)
            grid[rnd.next(n)][rnd.next(m)] = '.';
    } else if (mode == 2) {
        int barriers = rnd.next(1, max(1, n / 2));
        for (int b = 0; b < barriers; ++b) {
            int row = rnd.next(n);
            for (int j = 0; j < m; ++j)
                grid[row][j] = '#';
            grid[row][rnd.next(m)] = '.';
        }
    } else if (mode == 3) {
        int barriers = rnd.next(1, max(1, m / 2));
        for (int b = 0; b < barriers; ++b) {
            int col = rnd.next(m);
            for (int i = 0; i < n; ++i)
                grid[i][col] = '#';
            grid[rnd.next(n)][col] = '.';
        }
    } else if (mode == 4) {
        fill(grid.begin(), grid.end(), string(m, '#'));
        int rooms = rnd.next(1, 4);
        for (int r = 0; r < rooms; ++r) {
            int r1 = rnd.next(n), r2 = rnd.next(n);
            int c1 = rnd.next(m), c2 = rnd.next(m);
            if (r1 > r2) swap(r1, r2);
            if (c1 > c2) swap(c1, c2);
            for (int i = r1; i <= r2; ++i)
                for (int j = c1; j <= c2; ++j)
                    grid[i][j] = '.';
        }
    } else if (mode == 5) {
        fill(grid.begin(), grid.end(), string(m, '#'));
        int len = rnd.next(1, n * m);
        int row = rnd.next(n), col = rnd.next(m);
        for (int step = 0; step < len; ++step) {
            grid[row][col] = '.';
            if (rnd.next(0, 1) == 0) {
                int nextCol = col + (rnd.next(0, 1) == 0 ? -1 : 1);
                if (0 <= nextCol && nextCol < m) col = nextCol;
            } else {
                int nextRow = row + (rnd.next(0, 1) == 0 ? -1 : 1);
                if (0 <= nextRow && nextRow < n) row = nextRow;
            }
        }
    } else {
        n = rnd.next(15, 30);
        m = rnd.next(15, 30);
        grid.assign(n, string(m, '.'));
        int stripes = rnd.next(2, 6);
        for (int s = 0; s < stripes; ++s) {
            int row = rnd.next(n);
            for (int j = 0; j < m; j += rnd.next(2, 4))
                grid[row][j] = '#';
        }
    }

    int emptyCount = 0;
    for (const string& row : grid)
        emptyCount += count(row.begin(), row.end(), '.');

    int k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1 && emptyCount > 0) {
        k = rnd.next(1, emptyCount);
    } else if (kMode == 2 && emptyCount > 0) {
        k = min(1000000, emptyCount + rnd.next(0, 5));
    } else if (kMode == 3) {
        k = rnd.next(1, min(1000000, n * m));
    } else {
        k = rnd.next(1, 1000000);
    }

    println(n, m, k);
    for (const string& row : grid)
        println(row);

    return 0;
}
