#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h, w;
    if (mode == 0) {
        h = 1;
        w = rnd.next(1, 18);
    } else if (mode == 1) {
        h = rnd.next(1, 18);
        w = 1;
    } else if (mode == 2) {
        h = rnd.next(2, 4);
        w = rnd.next(2, 18);
    } else if (mode == 3) {
        h = rnd.next(2, 18);
        w = rnd.next(2, 4);
    } else {
        h = rnd.next(2, 12);
        w = rnd.next(2, 12);
    }

    vector<string> mines(h, string(w, '.'));
    int pattern = rnd.next(0, 5);
    int threshold = rnd.next(0, 100);
    int centerR = rnd.next(0, h - 1);
    int centerC = rnd.next(0, w - 1);
    int radius = rnd.next(0, max(h, w) / 3 + 1);
    if (pattern == 0) {
        threshold = rnd.next(5, 25);
    } else if (pattern == 1) {
        threshold = rnd.next(75, 95);
    } else if (pattern == 2) {
        threshold = rnd.next(30, 70);
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            bool mine = false;
            if (pattern <= 2) {
                mine = rnd.next(0, 99) < threshold;
            } else if (pattern == 3) {
                mine = ((i + j + rnd.next(0, 1)) % 2 == 0);
            } else if (pattern == 4) {
                mine = (i == 0 || j == 0 || i + 1 == h || j + 1 == w);
                if (rnd.next(0, 99) < 20) mine = !mine;
            } else {
                int dist = abs(i - centerR) + abs(j - centerC);
                mine = dist <= radius;
            }
            if (mine) mines[i][j] = 'X';
        }
    }

    vector<string> grid(h, string(w, '0'));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int count = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (0 <= ni && ni < h && 0 <= nj && nj < w &&
                        mines[ni][nj] == 'X') {
                        ++count;
                    }
                }
            }
            grid[i][j] = char('0' + count);
        }
    }

    println(h, w);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
