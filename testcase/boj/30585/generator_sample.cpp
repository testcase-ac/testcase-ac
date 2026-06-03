#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int h, w;

    if (mode == 0) {
        h = rnd.next(1, 3);
        w = rnd.next(1, 6);
    } else if (mode == 1) {
        h = rnd.next(1, 100);
        w = 1;
    } else if (mode == 2) {
        h = 1;
        w = rnd.next(1, 100);
    } else {
        h = rnd.next(2, 12);
        w = rnd.next(2, 12);
    }

    vector<string> grid(h, string(w, '0'));
    int fill = rnd.next(0, 1);

    if (mode == 0) {
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                grid[r][c] = char('0' + fill);
            }
        }
    } else if (mode == 1 || mode == 2) {
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                grid[r][c] = char('0' + ((r + c + fill) % 2));
            }
        }
    } else if (mode == 3) {
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                grid[r][c] = char('0' + fill);
            }
        }
        int flips = rnd.next(1, min(h * w, 5));
        for (int i = 0; i < flips; ++i) {
            int r = rnd.next(0, h - 1);
            int c = rnd.next(0, w - 1);
            grid[r][c] = char('0' + (1 - fill));
        }
    } else if (mode == 4) {
        vector<int> cells(h * w);
        for (int i = 0; i < h * w; ++i) {
            cells[i] = i;
        }
        shuffle(cells.begin(), cells.end());
        int ones = (h * w) / 2 + rnd.next(0, (h * w) % 2);
        for (int i = 0; i < ones; ++i) {
            grid[cells[i] / w][cells[i] % w] = '1';
        }
    } else if (mode == 5) {
        bool rowStripes = rnd.next(0, 1);
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                int stripe = rowStripes ? r : c;
                grid[r][c] = char('0' + ((stripe + fill) % 2));
            }
        }
    } else {
        int percentOnes = rnd.next(10, 90);
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                grid[r][c] = rnd.next(1, 100) <= percentOnes ? '1' : '0';
            }
        }
    }

    println(h, w);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
