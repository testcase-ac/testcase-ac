#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 18 : 12);
    vector<string> grid(n, string(n, '0'));

    if (mode == 0) {
        int ones = rnd.next(0, min(n * n, 10));
        vector<int> cells(n * n);
        for (int i = 0; i < n * n; ++i) cells[i] = i;
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < ones; ++i) {
            grid[cells[i] / n][cells[i] % n] = '1';
        }
    } else if (mode == 1) {
        int rowCount = rnd.next(1, min(n, 6));
        vector<int> rows(n);
        for (int i = 0; i < n; ++i) rows[i] = i;
        shuffle(rows.begin(), rows.end());
        for (int i = 0; i < rowCount; ++i) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, min(n - 1, l + rnd.next(0, 4)));
            for (int c = l; c <= r; ++c) grid[rows[i]][c] = '1';
        }
    } else if (mode == 2) {
        int top = rnd.next(0, n - 1);
        int bottom = rnd.next(top, n - 1);
        int width = rnd.next(1, min(n, 5));
        for (int r = top; r <= bottom; ++r) {
            int start;
            if ((r - top) % 2 == 0) {
                start = rnd.next(0, n - width);
            } else {
                start = max(0, n - width - rnd.next(0, min(n - width, 2)));
            }
            for (int c = start; c < start + width; ++c) grid[r][c] = '1';
        }
    } else if (mode == 3) {
        int r = rnd.next(0, n - 2);
        int leftEnd = rnd.next(0, n - 2);
        int rightStart = rnd.next(leftEnd + 1, n - 1);
        for (int c = 0; c <= leftEnd; ++c) grid[r][c] = '1';
        for (int c = rightStart; c < n; ++c) grid[r + 1][c] = '1';

        int extra = rnd.next(0, min(n, 5));
        for (int i = 0; i < extra; ++i) {
            int er = rnd.next(0, n - 1);
            int ec = rnd.next(0, n - 1);
            grid[er][ec] = '1';
        }
    } else if (mode == 4) {
        int h = rnd.next(1, min(n, 5));
        int w = rnd.next(1, min(n, 5));
        int top = rnd.next(0, n - h);
        int left = rnd.next(0, n - w);
        for (int r = top; r < top + h; ++r) {
            for (int c = left; c < left + w; ++c) {
                if (rnd.next(0, 3) != 0) grid[r][c] = '1';
            }
        }
    } else {
        int filledRows = rnd.next(1, min(n, 8));
        for (int i = 0; i < filledRows; ++i) {
            int r = rnd.next(0, n - 1);
            int l = rnd.next(0, n - 1);
            int rgt = rnd.next(l, n - 1);
            for (int c = l; c <= rgt; ++c) {
                if (rnd.next(0, 4) != 0) grid[r][c] = '1';
            }
        }
    }

    println(n);
    for (const string& row : grid) println(row);

    return 0;
}
