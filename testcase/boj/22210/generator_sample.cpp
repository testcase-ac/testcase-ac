#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int countAdjacentMines(const vector<string>& mines, int r, int c) {
    int h = int(mines.size());
    int w = int(mines[0].size());
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int nr = r + dr;
            int nc = c + dc;
            if (0 <= nr && nr < h && 0 <= nc && nc < w && mines[nr][nc] == 'X') {
                ++count;
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int h;
    int w;
    if (mode == 0) {
        h = 1;
        w = rnd.next(1, 18);
    } else if (mode == 1) {
        h = rnd.next(1, 4);
        w = 1;
    } else if (mode == 2) {
        h = rnd.next(2, 4);
        w = rnd.next(2, 12);
    } else if (mode == 3) {
        h = rnd.next(3, 4);
        w = rnd.next(8, 20);
    } else if (mode == 4) {
        h = rnd.next(1, 4);
        w = rnd.next(1, 16);
    } else {
        h = rnd.next(1, 4);
        w = rnd.next(1, 20);
    }

    vector<string> mines(h, string(w, '.'));
    if (mode == 0 || mode == 1) {
        double p = rnd.next(0.15, 0.85);
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if (rnd.next() < p) {
                    mines[r][c] = 'X';
                }
            }
        }
    } else if (mode == 2) {
        double p = rnd.any(vector<double>{0.08, 0.25, 0.5, 0.75, 0.92});
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if (rnd.next() < p) {
                    mines[r][c] = 'X';
                }
            }
        }
    } else if (mode == 3) {
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if ((r + c + rnd.next(0, 1)) % 3 == 0) {
                    mines[r][c] = 'X';
                }
            }
        }
    } else if (mode == 4) {
        char fill = rnd.next(0, 1) ? 'X' : '.';
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                mines[r][c] = fill;
            }
        }
        int flips = rnd.next(0, h * w);
        for (int i = 0; i < flips; ++i) {
            int r = rnd.next(0, h - 1);
            int c = rnd.next(0, w - 1);
            mines[r][c] = mines[r][c] == 'X' ? '.' : 'X';
        }
    } else {
        for (int c = 0; c < w; ++c) {
            char col = rnd.next(0, 1) ? 'X' : '.';
            for (int r = 0; r < h; ++r) {
                if (rnd.next(0, 9) < 8) {
                    mines[r][c] = col;
                } else {
                    mines[r][c] = col == 'X' ? '.' : 'X';
                }
            }
        }
    }

    println(h, w);
    for (int r = 0; r < h; ++r) {
        string row;
        for (int c = 0; c < w; ++c) {
            row += char('0' + countAdjacentMines(mines, r, c));
        }
        println(row);
    }

    return 0;
}
