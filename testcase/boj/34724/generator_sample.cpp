#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int m = rnd.next(2, 16);
    vector<string> grid(n, string(m, '0'));

    int mode = rnd.next(0, 6);

    if (mode == 0) {
        double p = rnd.next(0.05, 0.35);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (rnd.next() < p) grid[i][j] = '1';
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int l = rnd.next(0, m - 1);
            int r = rnd.next(l, m - 1);
            for (int j = l; j <= r; ++j) grid[i][j] = '1';
        }
    } else if (mode == 2) {
        for (int j = 0; j < m; ++j) {
            int top = rnd.next(0, n - 1);
            int bottom = rnd.next(top, n - 1);
            for (int i = top; i <= bottom; ++i) grid[i][j] = '1';
        }
    } else if (mode == 3) {
        int parity = rnd.next(0, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if ((i + j) % 2 == parity) grid[i][j] = '1';
    } else if (mode == 4) {
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, m - 1);
        fill(grid[row].begin(), grid[row].end(), '1');
        for (int i = 0; i < n; ++i) grid[i][col] = '1';
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j] == '0' && rnd.next() < 0.08) grid[i][j] = '1';
    } else {
        int h = rnd.next(2, min(n, 5));
        int w = rnd.next(2, min(m, 6));
        int top = rnd.next(0, n - h);
        int left = rnd.next(0, m - w);
        for (int i = top; i < top + h; ++i)
            for (int j = left; j < left + w; ++j)
                grid[i][j] = '1';

        double p = rnd.next(0.03, 0.20);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j] == '0' && rnd.next() < p) grid[i][j] = '1';
    }

    println(n, m);
    for (const string& row : grid) println(row);

    return 0;
}
